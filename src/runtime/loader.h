/*
 * loader.h
 *
 *  Created on: Dec 25, 2011
 *      Author: dazo
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NACL_DEFAULT_STACK_MAX  (16 << 20)  /* main thread stack */

struct NaClApp
{
  /* public, user settable prior to app start. */
  uint8_t addr_bits;

  /*
   * stack_size is the maximum size of the (main) stack.  The stack
   * memory is eager allocated (mapped in w/o MAP_NORESERVE) so
   * there must be enough swap space; page table entries are not
   * populated (no MAP_POPULATE), so actual accesses will likely
   * incur page faults.
   */
  uintptr_t stack_size;

  /* Determined at load time; OS-determined. Read-only after load. */
  uintptr_t mem_start;

  uintptr_t dispatch_thunk;

  /* only used for ET_EXEC:  for CS restriction */
  uintptr_t static_text_end; /* relative to mem_start */

  /*
   * The dynamic code area follows the static code area.  These fields
   * are both set to static_text_end if the dynamic code area has zero size.
   */
  uintptr_t dynamic_text_start;
  uintptr_t dynamic_text_end;

  /*
   * rodata_start and data_start may be 0 if these segments are not
   * present in the executable.
   */
  uintptr_t rodata_start; /* initialized data, ro */
  uintptr_t data_start; /* initialized data/bss, rw */
  uintptr_t data_end; /* see break_addr below */

  /*
   * initial_entry_pt is the first address in untrusted code to jump
   * to.  When using the IRT (integrated runtime), this is provided by
   * the IRT library, and user_entry_pt is the entry point in the user
   * executable.  Otherwise, initial_entry_pt is in the user
   * executable and user_entry_pt is zero.
   */
  uintptr_t initial_entry_pt;
  uintptr_t user_entry_pt;

  /*
   * bundle_size is the bundle alignment boundary for validation (16
   * or 32), so int is okay.  This value must be a power of 2.
   */
  int bundle_size;

  uintptr_t break_addr; /* user addr. data_end <= break_addr is an invariant */

  int exit_status; /* nexe exit code */

  struct Manifest *manifest; /* structure to hold proxy manifest, policy, zvm settings e.t.c. */
  void *signal_stack; /* Stack for signal handling, registered with sigaltstack(). */
  uintptr_t *syscall_args; /* arguments for the current syscall (trap()) */
  uint32_t sysret; /* syscall return code */
  uintptr_t sys_tls; /* only need for nexe prolog */
};

/*
 * target is an absolute address in the source region.  the patch code
 * will figure out the corresponding address in the destination region
 * and modify as appropriate.  this makes it easier to specify, since
 * the target is typically the address of some symbol from the source
 * template.
 */
struct NaClPatch {
  uintptr_t           target;
  uint64_t            value;
};

struct NaClPatchInfo {
  uintptr_t           dst;
  uintptr_t           src;
  size_t              nbytes;

  struct NaClPatch    *abs16;
  size_t              num_abs16;

  struct NaClPatch    *abs32;
  size_t              num_abs32;

  struct NaClPatch    *abs64;
  size_t              num_abs64;

  uintptr_t           *rel64;
  size_t              num_rel64;
};

struct NaClPatchInfo *NaClPatchInfoCtor(struct NaClPatchInfo *self);

void NaClApplyPatchToMemory(struct NaClPatchInfo *patch);

void NaClVmHoleWaitToStartThread(struct NaClApp *nap);

void NaClVmHoleThreadStackIsSafe(struct NaClApp *nap);

#ifdef __cplusplus
}
#endif

#endif /* LOADER_H_ */
