#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include "common/manifest_parser.h"
#include "runtime/loader.h"
#include "common/libnacl.h"

enum MAIN_ERR_CODES
{
  OK_CODE,
  FAIL_CODE
};

struct zvm_state {
	int debug_mode_bypass_acl_checks;
	int debug_mode_ignore_validator;
	int debug_mode_bypass_platform_qualification;
	int log_verbosity;
	char *manifest_filename;

};

/*
 * hold command line switches
 */
struct zvm_state
{
  int debug_mode_ignore_validator;
  int debug_mode_bypass_platform_qualification;
  int log_verbosity;
  char *manifest_filename;
};

#define CMD_SWITCHES "+lv:qM:" /* zvm switches in getopt() format */
static void print_usage()
{
  fprintf(stderr, /* must be keep up to CMD_SWITCHES */
          "Usage: zvm [-h] [-v<number>] [-a] [-l] [-v] [-q] -M<filename>\n"
          " -h print usage information\n"
          " -v sets log verbosity level"
          " -l enables debug mode for bypassing validator\n"
          " -q enabled debug mode for bypassing platform qualification\n"
          " -M sets manifest filename\n");
}

/*
 * parse command line. return 0 if successful
 */
int zvm_state_init(int argc, char **argv, struct zvm_state* st)
{
  int opt;
  memset(st, 0, 1); /* zero all zvm_state fields */

  /* parse command line */
  while((opt = getopt(argc, argv, CMD_SWITCHES)) != -1)
  {
    switch(opt)
    {
      case 'l':
        ++st->debug_mode_ignore_validator;
        LOG(WARN, "DEBUG MODE ENABLED (bypass validator)\n");
        break;
      case 'v':
        st->log_verbosity = atoi(optarg);
        log_set_verbosity(st->log_verbosity);
        LOG(WARN, "Log verbosity set %d\n", st->log_verbosity);
        break;
      case 'q':
        LOG(WARN, "DEBUG MODE ENABLED (bypass platform qualification)\n");
        st->debug_mode_bypass_platform_qualification = 1;
        break;
      case 'M':
        st->manifest_filename = optarg;
        break;
      default:
        LOG(FATAL, "Unrecognized option: [%c]\n\n", opt);
        print_usage();
        return FAIL_CODE;
    }
  }

  return OK_CODE;
}

/*
 * put command line information to the log
 */
void log_cmd_line(int argc, char **argv)
{
  int i;
  int pos;
  char buf[4096];
  int bufsize = sizeof(buf);

  pos = snprintf(buf, bufsize, "zvm argument list:");
  for(i = 0; (i < argc) && (pos < (bufsize - 2)); i++)
  {
    pos += snprintf(buf + pos, bufsize - pos - 2, " %s", argv[i]);
  }

  snprintf(buf + pos, bufsize - pos, "\n");
  LOG(INFO, buf);
}

int main(int argc, char **argv)
{
  struct NaClApp state;
  struct zvm_state st;

  /* parse command line */
  LOG(INFO, "ZeroVM starting...\n");
  zvm_state_init(argc, argv, &st);
  if(st.log_verbosity >= INFO) log_cmd_line(argc, argv);

  /* initialize manifest */
  if(!st.manifest_filename) LOG(FATAL, "manifest file name is empty\n");
  if (!parse_manifest(st.manifest_filename, &state))
    LOG(FATAL, "invalid manifest file '%s'\n", st.manifest_filename);

  /* initialize user policy, zerovm settings */
//  SetupUserPolicy(&state);
//  SetupSystemPolicy(&state);

  /* log setup */
  /* manifest setup (issue all actions given in manifest) */
  /* install trap() */
  /* load (and validate / skip validation) nexe/blob */
  /* install signal hooks */
  /* finish the nexe object setup */
  /* launch nexe and wait for a long jump */
  /* prepare report */


	signal_handlers_init();
	if (!st.debug_mode_bypass_platform_qualification)
	{
		if(platform_qualify())
			log(FATAL, "Platform qualification failed\n\n");
	}

  /* zerovm exit actions */
  LOG(INFO, "ZeroVM finished.\n");
  return OK_CODE;
}
