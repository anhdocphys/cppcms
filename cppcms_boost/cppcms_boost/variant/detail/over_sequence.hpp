//-----------------------------------------------------------------------------
// boost variant/detail/over_sequence.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Portions Copyright (C) 2002 David Abrahams
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPCMS_BOOST_VARIANT_DETAIL_OVER_SEQUENCE_HPP
#define CPPCMS_BOOST_VARIANT_DETAIL_OVER_SEQUENCE_HPP

#include "cppcms_boost/mpl/aux_/config/ctps.hpp"
#if defined(CPPCMS_BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   include "cppcms_boost/mpl/eval_if.hpp"
#   include "cppcms_boost/mpl/bool.hpp"
#   include "cppcms_boost/mpl/identity.hpp"
#   include "cppcms_boost/type.hpp"
#endif


namespace cppcms_boost {
namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) class over_sequence
//
// Wrapper used to indicate bounded types for variant are from type sequence.
//
template <typename Types>
struct over_sequence
{
    typedef Types type;
};

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction is_over_sequence (modeled on code by David Abrahams)
//
// Indicates whether the specified type is of form over_sequence<...> or not.
//

#if !defined(CPPCMS_BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T>
struct is_over_sequence
    : mpl::false_
{
};

template <typename Types>
struct is_over_sequence< over_sequence<Types> >
    : mpl::true_
{
};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

typedef char (&yes_over_sequence_t)[1];
typedef char (&no_over_sequence_t)[2];

no_over_sequence_t is_over_sequence_test(...);

template<typename T>
yes_over_sequence_t is_over_sequence_test(
      type< ::cppcms_boost::detail::variant::over_sequence<T> >
    );

template<typename T>
struct is_over_sequence_impl
{
    CPPCMS_BOOST_STATIC_CONSTANT(bool, value = (
          sizeof(is_over_sequence_test(type<T>()))
          == sizeof(yes_over_sequence_t)
        ));
};

template <typename T>
struct is_over_sequence
    : mpl::bool_<
          ::cppcms_boost::detail::variant::is_over_sequence_impl<T>::value
        >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

}} // namespace detail::variant
} // namespace boost

#endif // BOOST_VARIANT_DETAIL_OVER_SEQUENCE_HPP
