/*
 * Copyright 2010 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/* @file
 *
 * Implementation of effector subclass used only for service runtime's
 * gio_shm object for mapping/unmapping shared memory in *trusted*
 * address space.
 */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_DESC_NACL_DESC_EFFECTOR_TRUSTED_MEM_H_
#define NATIVE_CLIENT_SRC_TRUSTED_DESC_NACL_DESC_EFFECTOR_TRUSTED_MEM_H_

#include "include/nacl_base.h"
#include "include/portability.h"

#include "src/desc/nacl_desc_effector.h"

EXTERN_C_BEGIN

/*
 * This effector is a degenerate case used only during shutdown, and
 * as such doesn't do much.
 */

struct NaClDescEffectorTrustedMem {
  struct NaClDescEffector base;
};

extern
int NaClDescEffectorTrustedMemCtor(struct NaClDescEffectorTrustedMem *self);

EXTERN_C_END

#endif  // NATIVE_CLIENT_SRC_TRUSTED_DESC_NACL_DESC_EFFECTOR_TRUSTED_MEM_H_
