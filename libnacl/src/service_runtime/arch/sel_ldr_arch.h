/*
 * Copyright 2009 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * This file switches to the architecture-specific header and
 * otherwise has no content.  There is no need for an inclusion guard,
 * but we include one to conform to the style rules.
 */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_ARCH_SEL_LDR_ARCH_H_
#define NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_ARCH_SEL_LDR_ARCH_H_

#include "include/nacl_base.h"

#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86
#include "src/service_runtime/arch/x86/sel_ldr_x86.h"
#elif NACL_ARCH(NACL_BUILD_ARCH) == NACL_arm
#include "src/service_runtime/arch/arm/sel_ldr_arm.h"
#else
#error Unknown platform!
#endif

#endif  /* NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_ARCH_SEL_LDR_ARCH_H_ */
