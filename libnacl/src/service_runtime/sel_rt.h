/*
 * Copyright 2009 The Native Client Authors.  All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

#ifndef NATIVE_CLIENT_SERVICE_RUNTIME_SEL_RT_H__
#define NATIVE_CLIENT_SERVICE_RUNTIME_SEL_RT_H__ 1

#include "include/nacl_base.h"

#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86
#include "src/service_runtime/arch/x86/sel_rt.h"
#elif NACL_ARCH(NACL_BUILD_ARCH) == NACL_arm
#include "src/service_runtime/arch/arm/sel_rt.h"
#else
#error Unknown platform!
#endif

struct NaClApp; /* fwd */

void      NaClInitGlobals();

uintptr_t NaClGetThreadCtxSp(struct NaClThreadContext  *th_ctx);

void      NaClSetThreadCtxSp(struct NaClThreadContext  *th_ctx, uintptr_t sp);

#endif  /* NATIVE_CLIENT_SERVICE_RUNTIME_SEL_RT_H__ */
