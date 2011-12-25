/*
 * logger.c
 *
 *  Created on: Dec 24, 2011
 *      Author: dazo
 */
#include <stdarg.h>
void NaClLog(int, char const*, ...);
void log(int detail_level, char const  *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	NaClLog(detail_level, fmt, ap);
	va_end(ap);
}
void NaClLogSetFile(char const *log_file);
void log_set_file(char const *log_file) {
  NaClLogSetFile(log_file);
}

void NaClLogSetVerbosity(int verb);
void log_set_verbosity(int verbosity) {
	NaClLogSetVerbosity(verbosity);
}
