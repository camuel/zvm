/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "src/platform/nacl_host_desc.h"
#include "src/platform/nacl_log.h"
#include "src/service_runtime/nacl_app_thread.h"
#include "src/service_runtime/sel_ldr.h"
#include "src/desc/nacl_desc_base.h"
#include "src/desc/nacl_desc_io.h"
#include "src/desc/nrd_all_modules.h"

#include "gtest/gtest.h"

//
// There are several problems in how these tests are set up.
//
// 1. NaCl modules such as the Log module are supposed to be
// initialized at process startup and finalized at shutdown.  In
// particular, there should not be any threads other than the main
// thread running when the Log module initializes, since the verbosity
// level is set then -- and thereafter it is assumed to be invariant
// and read without acquring locks.  If any threads are left running
// (e.g., NaClApp internal service threads), then race detectors would
// legitimately report an error which is inappropriate because the
// test is ignoring the API contract.
//
// 2. NaClApp objects, while they don't have a Dtor, are expected to
// have a lifetime equal to that of the process that contain them.  In
// particular, when the untrusted thread invokes the exit syscall, it
// expects to be able to use _exit to exit, killing all other
// untrusted threads as a side effect.  Furthermore, once a NaClApp
// object is initialized and NaClAppLaunchServiceThreads invoked,
// system service threads are running holding references to the
// NaClApp object.  If the NaClApp object goes out of scope or is
// otherwise destroyed and its memory freed, then these system thread
// may access memory that is no longer valid.  Tests cannot readily be
// written to cleanly exercise the state space of a NaClApp after
// NaClAppLaunchServiceThreads unless the test process exits---thereby
// killing the service threads as a side-effect---when each individual
// test is complete.
//
// These tests do not invoke NaClAppLaunchServiceThreads, so there
// should be no service threads left running between tests.

class SelLdrTest : public testing::Test {
 protected:
  virtual void SetUp();
  virtual void TearDown();
};

void SelLdrTest::SetUp() {
  NaClNrdAllModulesInit();
}

void SelLdrTest::TearDown() {
  NaClNrdAllModulesFini();
}

// set, get, setavail operations on the descriptor table
TEST_F(SelLdrTest, DescTable) {
  struct NaClApp app;
  struct NaClHostDesc *host_desc;
  struct NaClDesc* io_desc;
  struct NaClDesc* ret_desc;
  int ret_code;

  ret_code = NaClAppCtor(&app);
  ASSERT_EQ(1, ret_code);

  host_desc = (struct NaClHostDesc *) malloc(sizeof *host_desc);
  if (NULL == host_desc) {
    fprintf(stderr, "No memory\n");
  }
  ASSERT_TRUE(NULL != host_desc);

  io_desc = (struct NaClDesc *) NaClDescIoDescMake(host_desc);

  // 1st pos available is 0
  ret_code = NaClSetAvail(&app, io_desc);
  ASSERT_EQ(0, ret_code);
  // valid desc at pos 0
  ret_desc = NaClGetDesc(&app, 0);
  ASSERT_TRUE(NULL != ret_desc);

  // next pos available is 1
  ret_code = NaClSetAvail(&app, NULL);
  ASSERT_EQ(1, ret_code);
  // no desc at pos 1
  ret_desc = NaClGetDesc(&app, 1);
  ASSERT_TRUE(NULL == ret_desc);

  // no desc at pos 1 -> pos 1 is available
  ret_code = NaClSetAvail(&app, io_desc);
  ASSERT_EQ(1, ret_code);

  // valid desc at pos 1
  ret_desc = NaClGetDesc(&app, 1);
  ASSERT_TRUE(NULL != ret_desc);

  // set no desc at pos 3
  NaClSetDesc(&app, 3, NULL);

  // valid desc at pos 4
  NaClSetDesc(&app, 4, io_desc);
  ret_desc = NaClGetDesc(&app, 4);
  ASSERT_TRUE(NULL != ret_desc);

  // never set a desc at pos 10
  ret_desc = NaClGetDesc(&app, 10);
  ASSERT_TRUE(NULL == ret_desc);
}

// add and remove operations on the threads table
// Remove thread from an empty table is tested in a death test.
// TODO(tuduce): specify the death test name when checking in.
TEST_F(SelLdrTest, ThreadTableTest) {
  struct NaClApp app;
  struct NaClAppThread nat, *appt=&nat;
  int ret_code;

  ret_code = NaClAppCtor(&app);
  ASSERT_EQ(1, ret_code);

  // 1st pos available is 0
  ASSERT_EQ(0, app.num_threads);
  ret_code = NaClAddThread(&app, appt);
  ASSERT_EQ(0, ret_code);
  ASSERT_EQ(1, app.num_threads);

  // next pos available is 1
  ret_code = NaClAddThread(&app, NULL);
  ASSERT_EQ(1, ret_code);
  ASSERT_EQ(2, app.num_threads);

  // no thread at pos 1 -> pos 1 is available
  ret_code = NaClAddThread(&app, appt);
  ASSERT_EQ(1, ret_code);
  ASSERT_EQ(3, app.num_threads);

  NaClRemoveThread(&app, 0);
  ASSERT_EQ(2, app.num_threads);
}
