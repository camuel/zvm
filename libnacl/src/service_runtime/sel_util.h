/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * NaCl Simple/secure ELF loader (NaCl SEL) misc utilities.
 */
#ifndef NATIVE_CLIENT_SERVICE_RUNTIME_SEL_UTIL_H_
#define NATIVE_CLIENT_SERVICE_RUNTIME_SEL_UTIL_H_ 1

#include <sys/types.h>

#include "include/nacl_base.h"
#include "include/portability.h"

#include "src/service_runtime/nacl_config.h"

EXTERN_C_BEGIN

#include "src/service_runtime/sel_util-inl.h"

typedef uint64_t tick_t;
tick_t get_ticks();

EXTERN_C_END

#endif  /* NATIVE_CLIENT_SERVICE_RUNTIME_SEL_UTIL_H_ */
