/*
 * libnacl.c
 *
 *  Created on: Dec 25, 2011
 *      Author: dazo
 */


#include <stdarg.h>
#include "libnacl.h"

/*
 * LIBNACL signatures list begin
 * Exhaustive list of all functions used from libnacl
 * */
void NaClLog(int, char const*, ...);
void NaClLogSetFile(char const *log_file);
void NaClLogSetVerbosity(int verb);
void NaClSignalHandlerInit();
int NaClRunSelQualificationTests();
/* LIBNACL signatures list end */



void log(int detail_level, char const  *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	NaClLog(detail_level, fmt, ap);
	va_end(ap);
}
void log_set_file(char const *log_file) {
  NaClLogSetFile(log_file);
}

void log_set_verbosity(int verbosity) {
	NaClLogSetVerbosity(verbosity);
}

void signal_handlers_init() {
	NaClSignalHandlerInit();
}

int platform_qualify() {
	return NaClRunSelQualificationTests();
}
