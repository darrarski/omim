#pragma once
#include "base.hpp"
#include "internal/message.hpp"
#include "src_point.hpp"
#include "../std/string.hpp"
#include "../std/vector.hpp"

namespace my
{
  // Called when ASSERT, CHECK or VERIFY failed.
  typedef void (*AssertFailedFn)(SrcPoint const &, string const &);
  extern AssertFailedFn OnAssertFailed;

  /// @return Pointer to previous message function.
  AssertFailedFn SetAssertFunction(AssertFailedFn fn);
}

// TODO: Evaluate X only once in CHECK().
#define CHECK(X, msg) if (X) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X")", ::my::impl::Message msg));}
#define CHECK_EQUAL(X, Y, msg) if ((X) == (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" == "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_NOT_EQUAL(X, Y, msg) if ((X) != (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" != "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_LESS(X, Y, msg) if ((X) < (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" < "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_LESS_OR_EQUAL(X, Y, msg) if ((X) <= (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" <= "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_GREATER(X, Y, msg) if ((X) > (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" > "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_GREATER_OR_EQUAL(X, Y, msg) if ((X) >= (Y)) {} else { \
  ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg("CHECK("#X" >= "#Y")", \
                                                   ::my::impl::Message(X, Y), \
                                                   ::my::impl::Message msg));}
#define CHECK_OR_CALL(fail, call, X, msg) if (X) {} else { \
  if (fail) {\
    ::my::OnAssertFailed(SRC(), ::my::impl::MergeMsg(::my::impl::Message("CHECK("#X")"), \
                                                     ::my::impl::Message msg)); \
  } else { \
    call(); \
  } }

#ifdef DEBUG
// for Symbian compatibility
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(X, msg) CHECK(X, msg)
#define VERIFY(X, msg) CHECK(X, msg)
#define ASSERT_EQUAL(X, Y, msg) CHECK_EQUAL(X, Y, msg)
#define ASSERT_NOT_EQUAL(X, Y, msg) CHECK_NOT_EQUAL(X, Y, msg)
#define ASSERT_LESS(X, Y, msg) CHECK_LESS(X, Y, msg)
#define ASSERT_LESS_OR_EQUAL(X, Y, msg) CHECK_LESS_OR_EQUAL(X, Y, msg)
#define ASSERT_GREATER(X, Y, msg) CHECK_GREATER(X, Y, msg)
#define ASSERT_GREATER_OR_EQUAL(X, Y, msg) CHECK_GREATER_OR_EQUAL(X, Y, msg)
#else
// for Symbian compatibility
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(X, msg)
#define VERIFY(X, msg) (X)
#define ASSERT_EQUAL(X, Y, msg)
#define ASSERT_NOT_EQUAL(X, Y, msg)
#define ASSERT_LESS(X, Y, msg)
#define ASSERT_LESS_OR_EQUAL(X, Y, msg)
#define ASSERT_GREATER(X, Y, msg)
#define ASSERT_GREATER_OR_EQUAL(X, Y, msg)
#endif
