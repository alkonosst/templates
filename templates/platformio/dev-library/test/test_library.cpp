/**
 * SPDX-FileCopyrightText: 2026 Maximiliano Ramirez <maximiliano.ramirezbravo@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <unity.h>

#ifdef ARDUINO
#  include <Arduino.h>
#endif

#include <MyLib.h>
using namespace MyLib;

/* ---------------------------------------------------------------------------------------------- */
/*                                              Tests                                             */
/* ---------------------------------------------------------------------------------------------- */

void test_something() {
  TEST_ASSERT_TRUE(true);
  TEST_ASSERT_FALSE(false);
}

/* ---------------------------------------------------------------------------------------------- */
/*                                             Runners                                            */
/* ---------------------------------------------------------------------------------------------- */

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_something);
  return UNITY_END();
}

// For native
int main(void) { return runUnityTests(); }

// For Arduino framework
#ifdef ARDUINO
void setup() {
  delay(2000);
  runUnityTests();
}
void loop() {}
#endif
