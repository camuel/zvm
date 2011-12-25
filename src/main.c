#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common/libnacl.h"
struct zvm_state {
	int debug_mode_bypass_acl_checks;
	int debug_mode_ignore_validator;
	int debug_mode_bypass_platform_qualification;
	int log_verbosity;
	char *manifest_filename;
};
void zvm_state_init(struct zvm_state* st) {
	st->debug_mode_bypass_acl_checks = 0;
	st->debug_mode_ignore_validator = 0;
	st->debug_mode_bypass_platform_qualification = 0;
	st->log_verbosity = 0;
	st->manifest_filename = NULL;
}
static void print_usage() {
  fprintf(stderr,
          "Usage: zvm [-h] [-v<number>] [-a] [-l] [-v] [-q] -M<filename>\n"
          " -h print usage information\n"
		  " -v sets log verbosity level"
          " -a enables debug mode for bypassing acl\n"
          " -l enables debug mode for bypassing validator\n"
		  " -q enabled debug mode for bypassing platform qualification\n"
		  " -M sets manifest filename\n");
}
int main(int argc, char **argv) {
	log(INFO, "ZeroVM starting...\n");
	struct zvm_state st;
	int opt;
    while ((opt = getopt(argc, argv, "+alv:qM:"))
    		!= -1) { switch (opt) {
    	case 'a':
    		log(WARN,  "DEBUG MODE ENABLED (bypass acl)\n");
    		st.debug_mode_bypass_acl_checks = 1;
    		break;
    	case 'l':
    		++st.debug_mode_ignore_validator;
    		log(WARN, "DEBUG MODE ENABLED (bypass validator)\n");
    		break;
    	case 'v':
    		st.log_verbosity = atoi(optarg);
    		log_set_verbosity(st.log_verbosity);
    		log(WARN, "Log verbosity set %d\n", st.log_verbosity);
    		break;
    	case 'q':
    	  	log(WARN, "DEBUG MODE ENABLED (bypass platform qualification)\n");
    	  	st.debug_mode_bypass_platform_qualification = 1;
    	  	break;
        case 'M':
        	st.manifest_filename = optarg;
        	break;
    	default:
    	  	log(FATAL, "Unrecognized option: [%c]\n\n", opt);
    	  	print_usage();
    	  	return -1;
    } }
	if (st.log_verbosity >= INFO) //log command line arguments
	{
		int i, pos;
		char buf[4096];
		int bufsize = sizeof(buf);
		pos = snprintf(buf, bufsize, "zvm argument list:");
		for (i = 0; (i < argc) && (pos < (bufsize - 2)); i++) {
			pos += snprintf(buf + pos, bufsize - pos - 2, " %s", argv[i]);
		}
		snprintf(buf + pos, bufsize - pos, "\n");
		log(INFO, buf);
	}

	signal_handlers_init();
	if (!st.debug_mode_bypass_platform_qualification)
	{
		if(platform_qualify())
			log(FATAL, "Platform qualification failed\n\n");
	}

	log(INFO, "ZeroVM finished.\n");
	return 0;
}
