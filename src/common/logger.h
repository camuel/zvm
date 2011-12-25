/*
 * logger.h
 *
 *  Created on: Dec 24, 2011
 *      Author: dazo
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#define INFO    (-1)
#define WARN    (-2)
#define ERROR   (-3)
#define FATAL   (-4)

void log(int detail_level, char const  *fmt, ...)
	__attribute__((format(printf, 2, 3)));

void log_set_file(char const *log_file);

void log_set_verbosity(int verbosity);

#endif /* LOGGER_H_ */
