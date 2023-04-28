#pragma once

// #define DEBUG
// #define DEBUG_NEW

#ifdef DEBUG_NEW
#include "../utils/debug_new.h"
#define new new(1)
#endif

#ifdef DEBUG
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_CONFIG_IMPLEMENT
#include "../utils/doctest.h"
#endif
#endif

#ifdef DEBUG
#define test doctest::Context().run()
#else
#define test
#endif

#ifdef DEBUG_NEW
#define leaks allocator::get_instance().checkMemoryLeaks()
#else
#define leaks
#endif