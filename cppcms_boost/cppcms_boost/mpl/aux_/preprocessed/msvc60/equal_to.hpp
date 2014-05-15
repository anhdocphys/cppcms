
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace cppcms_boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , CPPCMS_BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = CPPCMS_BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , CPPCMS_BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = CPPCMS_BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        CPPCMS_BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        CPPCMS_BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        CPPCMS_BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename CPPCMS_BOOST_MPL_AUX_NA_PARAM(N1)
    , typename CPPCMS_BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    CPPCMS_BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

CPPCMS_BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace cppcms_boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        CPPCMS_BOOST_STATIC_CONSTANT(bool, value =
             ( CPPCMS_BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             CPPCMS_BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}