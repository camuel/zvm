/*
 * manifest_parse.h
 *
 *  Created on: Nov 1, 2011
 *      Author: d'b
 */
#ifndef SERVICE_RUNTIME_MANIFEST_PARSER_H__
#define SERVICE_RUNTIME_MANIFEST_PARSER_H__ 1

#include "include/nacl_base.h"
#include "src/service_runtime/nacl_config.h"
#include "src/service_runtime/sel_ldr.h"

#define MANIFEST_VERSION "11nov2011"
#define EOL "\r\n"

#define ALL_KEYS {"version", "zerovm", "nexe", "maxnexe", "input", "maxinput", "#etag", "#content-type", "#x-timestamp",\
"#x-object-meta-tag", "input_mnfst", "output", "maxoutput", "output_mnfst", "maxmnfstline", "maxmnfstlines", "timeout",\
"kill_timeout", "?zerovm_retcode", "?zerovm_status", "?etag", "?#retcode", "?#status", "?#content-type", "?#x-object-meta-tag"}
#define USER_KEYS {"#etag", "#content-type", "#x-timestamp", "#x-object-meta-tag"}
#define ANSWER_KEYS {"?zerovm_retcode", "?zerovm_status", "?etag", "?#retcode", "?#status", "?#content-type", "?#x-object-meta-tag"}

EXTERN_C_BEGIN
/*
 * open manifest file, parse it and initialize in the given
 * NaClApp structure two fields: "manifest" and "manifest_size"
 */
int ParseManifest(const char *name, struct NaClApp *nap);

/*
 * get value by key from the manifest. if not found - NULL
 */
char* GetValueByKey(struct NaClApp *nap, char *key);

/*
 * return number of found values from manifest by given key
 * values will be stored into provided array
 * note: this is temporary function. needed to solve the problem of
 * duplicate keys in manifest
 */
int GetValuesByKey(struct NaClApp *nap, char *key, char *values[], int capacity);

/*
 * public function. set value in manifest by given key
 * return 1 if success, otherwise - 0
 */
int SetValueByKey(struct NaClApp *nap, char *key, char *value);

/*
 * helper procedures. were put here for unit test
 */
char* CutSpaces(char *a);
char* GetKey(char *a);
char* GetValue(char *a);

EXTERN_C_END

#endif
