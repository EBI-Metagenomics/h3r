#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H

#include <assert.h>

#define h3r_static_assert(test_for_true)                                       \
  static_assert((test_for_true), "(" #test_for_true ") failed")

#endif
