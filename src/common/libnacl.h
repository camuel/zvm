/*
 * libnacl.h
 *
 *  Created on: Dec 25, 2011
 *      Author: dazo
 */

#ifndef LIBNACL_H_
#define LIBNACL_H_

#define INFO    (-1)
#define WARN    (-2)
#define ERROR   (-3)
#define FATAL   (-4)

#define LOG(lvl, ...) zvmlog(lvl, __VA_ARGS__)

void log_set_file(char const *log_file);

void log_set_verbosity(int verbosity);

void signal_handlers_init();

int platform_qualify();

#endif /* LIBNACL_H_ */
