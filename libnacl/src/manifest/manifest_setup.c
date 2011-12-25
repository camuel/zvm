/*
 * manifest_setup.c
 *
 *  Created on: Nov 30, 2011
 *      Author: d'b
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "src/service_runtime/include/bits/mman.h"
#include "src/service_runtime/sel_ldr.h"
#include "src/manifest/manifest_parser.h"
#include "src/service_runtime/nacl_config.h"
#include "src/service_runtime/sel_mem.h"
#include "src/service_runtime/nacl_memory_object.h"
#include "src/platform/nacl_log.h"

#include <src/manifest/manifest_parser.h>
#include <src/manifest/manifest_setup.h>
#include "src/service_runtime/nacl_syscall_common.h"
/*
 * set "prefix" (channel name) by "ch" (channel id)
 * note: prefix must have enough space to hold it
 */
static void GetChannelPrefixById(enum ChannelType ch, char *prefix)
{
  char *prefixes[] = CHANNEL_PREFIXES;
  COND_ABORT(ch >= sizeof(prefixes)/sizeof(*prefixes), "unknown channel id\n");
  strcpy(prefix, prefixes[ch]);
}

/*
 * construct i/o channel and update SetupList with not mounted channel
 * if successful return 0, otherwise - 1
 * note: SetupList object must be allocated
 */
int32_t ConstructChannel(struct NaClApp *nap, enum ChannelType ch)
{
  /* allocate channel */
  char prefix[1024];
  struct PreOpenedFileDesc *channel = &nap->manifest->user_setup->channels[ch];
  channel->self_size = sizeof(*channel); /* set self size */
  GetChannelPrefixById(ch, prefix);

  // ### rewrite it! we must detect not set keywords and make default action (or set default value)
#define SET_LIMIT(a, limit)\
  do {\
    char str[1024];\
    char *p;\
    if(!limit) break;\
    sprintf(str, "%s%s", prefix, limit);\
    p = GetValueByKey(nap, str);\
    a = p ? atoll(p) : 0;\
  } while (0);

  /* check if channel is set in manifest and set main attributes */
  channel->name = (uint64_t)GetValueByKey(nap, prefix);
  if(!channel->name) return 1;
  SET_LIMIT(channel->mounted, "Mode");
  channel->type = ch;

  /* set limits */
  SET_LIMIT(channel->max_size, "Max");
  SET_LIMIT(channel->max_get_size, "MaxGet");
  SET_LIMIT(channel->max_gets, "MaxGetCnt");
  SET_LIMIT(channel->max_put_size, "MaxPut");
  SET_LIMIT(channel->max_puts, "MaxPutCnt");

  /* set counters */
  channel->cnt_get_size = 0;
  channel->cnt_gets = 0;
  channel->cnt_put_size = 0;
  channel->cnt_puts = 0;

#undef SET_LIMIT
  return 0;
}

/*
 * return md5 hash of mapped _output_ file (or NULL)
 */
char* MakeEtag(struct NaClApp *nap)
{
//  uintptr_t addr;

  /* check if output file exists */
  if(!nap->manifest->user_setup->channels[OutputChannel].name) return NULL;
  return "etag disabled";

  /* calculate effective sys address from nexe address space */
//  //### BUG!!! need additional check no assumtions!
//  assert(nap->manifest->user_setup->channels[OutputChannel].buffer);
//  addr = NaClUserToSys(nap, (uint32_t) nap->manifest->user_setup->channels[OutputChannel].buffer);
//  return MD5((unsigned char*)addr, (uint32_t)nap->manifest->user_setup->channels[OutputChannel].bsize);
}

/*
 * construct Report (zerovm report to proxy) part of manifest structure
 * note: malloc(). must be called only once
 */
void SetupReportSettings(struct NaClApp *nap)
{
  /* allocate space for report */
  struct Report *report = malloc(sizeof(*report)); // ### memory must be allocated before nexe start
  COND_ABORT(!report, "cannot allocate memory for report\n");

  /* set results */
  report->etag = MakeEtag(nap);
  report->content_type = "application/octet-stream"; // where to get it?
  report->x_object_meta_tag = "Format:Pickle"; // where to get it?

  /* ### ret codes must be set from main() */
  nap->manifest->report = report;
}

/*
 * return string containing answer to proxy (or NULL)
 * note: "report" must have enough space to hold a new string
 * "MAX_MANIFEST_LEN" would be enough since report is subset of master manifest
 */
void AnswerManifestPut(struct NaClApp *nap, char *report)
{
  sprintf(report,
    "ReportRetCode        =%d\n"
    "ReportEtag           =%s\n"
    "ReportUserRetCode    =%d\n"
    "ReportContentType    =%s\n"
    "ReportXObjectMetaTag =%s\n",
    nap->manifest->report->ret_code,
    nap->manifest->report->etag,
    nap->manifest->report->user_ret_code,
    nap->manifest->report->content_type,
    nap->manifest->report->x_object_meta_tag);
}

#define TRANSET(var, str)\
  do {\
    char *p = GetValueByKey(nap, str);\
    var = p == NULL ? 0 : atoll(p);\
  } while(0)

/*
 * construct SetupList (policy) part of manifest structure (w/o channels)
 * note: malloc(). must be called only once
 */
void SetupUserPolicy(struct NaClApp *nap)
{
  /* allocate space for policy */
  struct SetupList *policy = malloc(sizeof(*policy));
  COND_ABORT(!policy, "cannot allocate memory for user policy\n");
  policy->self_size = sizeof(*policy); /* set self size */

  /* setup limits */
  TRANSET(policy->max_cpu, "CPUMax");
  TRANSET(policy->max_mem, "MemMax");
  TRANSET(policy->max_setup_calls, "SetupCallsMax");
  TRANSET(policy->max_syscalls, "SyscallsMax");

  /* setup counters */
  policy->cnt_cpu = 0;
  policy->cnt_cpu_last = 0;
  policy->cnt_mem = 0;
  policy->cnt_setup_calls = 0;
  policy->cnt_syscalls = 0;
  policy->heap_ptr = 0; /* set user heap to NULL until it allocated */

  /* clear syscallback */
  policy->syscallback = 0;

  /* setup custom attributes */
#define STRNCPY_NULL(a, b, n) if ((a) && (b)) strncpy(a, b, n);
  STRNCPY_NULL(policy->content_type, GetValueByKey(nap, "ContentType"), CONTENT_TYPE_LEN);
  STRNCPY_NULL(policy->timestamp, GetValueByKey(nap, "TimeStamp"), TIMESTAMP_LEN);
  STRNCPY_NULL(policy->x_object_meta_tag, GetValueByKey(nap, "XObjectMetaTag"), X_OBJECT_META_TAG_LEN);
  STRNCPY_NULL(policy->user_etag, GetValueByKey(nap, "UserETag"), USER_TAG_LEN);
#undef STRNCPY_NULL
  nap->manifest->user_setup = policy;
}

/*
 * construct SystemList (zerovm settings) part of manifest structure
 * note: malloc(). must be called only once
 */
void SetupSystemPolicy(struct NaClApp *nap)
{
  /* allocate space for policy */
  struct SystemList *policy = malloc(sizeof(*policy));
  COND_ABORT(!policy, "cannot allocate memory for system policy\n");

  /* get zerovm settings */
  policy->version = GetValueByKey(nap, "Version");
  policy->zerovm = GetValueByKey(nap, "ZeroVM");
  policy->log = GetValueByKey(nap, "Log");
  policy->report = GetValueByKey(nap, "Report");
  policy->nexe = GetValueByKey(nap, "Nexe");
  policy->cmd_line = GetValueByKey(nap, "CommandLine");
  policy->blob = GetValueByKey(nap, "Blob");
  policy->nexe_etag = GetValueByKey(nap, "NexeEtag");

  TRANSET(policy->nexe_max, "NexeMax");
  TRANSET(policy->timeout, "Timeout");
  TRANSET(policy->kill_timeout, "KillTimeout");

  nap->manifest->system_setup = policy;
}

/* ### temporary disabled
 * preallocate memory area of given size. abort if fail
 */
void PreallocateUserMemory(struct NaClApp *nap)
{
  return; // ###

//  struct SetupList *policy = nap->manifest->user_setup;
//  policy->heap_ptr = NaClCommonSysMmapIntern(nap, 0, policy->max_mem, 3, 0x22, -1, 0);
//
//  /* why 0xfffff000? 1. 0x1000 reserved for error codes 2. it is still larger then 4gb - stack */
//  COND_ABORT(policy->heap_ptr > 0xfffff000, "cannot preallocate memory for user\n");
}

/*
 * user accounting. SetupList object counters
 * all accounting procedures return 0 if succes and -1 if fail
 */

/* system counters */
#define INCNT(cnt) if(nap->manifest) {++nap->manifest->user_setup->cnt; return 0;} return -1
#define DECNT(cnt) if(nap->manifest) {--nap->manifest->user_setup->cnt; return 0;} return -1

int32_t AccountingSyscallsInc(struct NaClApp *nap) { INCNT(cnt_syscalls); }
int32_t AccountingSyscallsDec(struct NaClApp *nap) { INCNT(cnt_syscalls); }
int32_t AccountingMemInc(struct NaClApp *nap) { INCNT(cnt_mem); }
int32_t AccountingMemDec(struct NaClApp *nap) { INCNT(cnt_mem); }
int32_t AccountingSetupcallsInc(struct NaClApp *nap) { INCNT(cnt_setup_calls); }
int32_t AccountingSetupcallsDec(struct NaClApp *nap) { INCNT(cnt_setup_calls); }

/* channel counters */
#define INCHCNT(ch, cnt) if(nap->manifest) {++nap->manifest->user_setup->channels[ch].cnt; return 0;} return -1
#define DECHCNT(ch, cnt) if(nap->manifest) {--nap->manifest->user_setup->channels[ch].cnt; return 0;} return -1

int32_t AccountingGetsInc(struct NaClApp *nap, enum ChannelType ch) { INCHCNT(ch, cnt_gets); }
int32_t AccountingGetsDec(struct NaClApp *nap, enum ChannelType ch) { DECHCNT(ch, cnt_gets); }
int32_t AccountingPutsInc(struct NaClApp *nap, enum ChannelType ch) { INCHCNT(ch, cnt_puts); }
int32_t AccountingPutsDec(struct NaClApp *nap, enum ChannelType ch) { DECHCNT(ch, cnt_puts); }
int32_t AccountingGetSizeInc(struct NaClApp *nap, enum ChannelType ch) { INCHCNT(ch, cnt_get_size); }
int32_t AccountingGetSizeDec(struct NaClApp *nap, enum ChannelType ch) { DECHCNT(ch, cnt_get_size); }
int32_t AccountingPutSizeInc(struct NaClApp *nap, enum ChannelType ch) { INCHCNT(ch, cnt_put_size); }
int32_t AccountingPutSizeDec(struct NaClApp *nap, enum ChannelType ch) { DECHCNT(ch, cnt_put_size); }
