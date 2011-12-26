/*
 * manifest_parse.h
 *
 *  Created on: Nov 1, 2011
 *      Author: d'b
 */
#ifndef SERVICE_RUNTIME_MANIFEST_PARSER_H__
#define SERVICE_RUNTIME_MANIFEST_PARSER_H__ 1

#include "runtime/loader.h"

#define MANIFEST_VERSION "11nov2011"
#define EOL "\r\n"

/*
 * open manifest file, parse it and initialize in the given
 * NaClApp structure two fields: "manifest" and "manifest_size"
 */
int parse_manifest(const char *name, struct NaClApp *nap);

/*
 * get value by key from the manifest. if not found - NULL
 */
char* get_value_by_key(struct NaClApp *nap, char *key);

/*
 * helper procedures. were put here for unit test
 */
char* cut_spaces(char *a);
char* get_key(char *a);
char* get_value(char *a);

#endif
