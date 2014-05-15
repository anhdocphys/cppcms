// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef CPPCMS_BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
#define CPPCMS_BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cppcms_boost/config.hpp> // BOOST_MSVC.
#include <cppcms_boost/detail/workaround.hpp>           
#include <cppcms_boost/iostreams/detail/template_params.hpp>
#include <cppcms_boost/iostreams/traits.hpp>
#include <cppcms_boost/mpl/bool.hpp>
#include <cppcms_boost/preprocessor/punctuation/comma_if.hpp>
#include <cppcms_boost/preprocessor/repetition/enum_params.hpp>
#include <cppcms_boost/static_assert.hpp>
#if CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_MSVC, < 1300)
# include <cppcms_boost/type_traits/is_base_and_derived.hpp>
#endif

#define CPPCMS_BOOST_IOSTREAMS_PIPABLE(filter, arity) \
    template< CPPCMS_BOOST_PP_ENUM_PARAMS(arity, typename T) \
              CPPCMS_BOOST_PP_COMMA_IF(arity) typename Component> \
    ::cppcms_boost::iostreams::pipeline< \
        ::cppcms_boost::iostreams::detail::pipeline_segment< \
            filter CPPCMS_BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T) \
        >, \
        Component \
    > operator|( const filter CPPCMS_BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T)& f, \
                 const Component& c ) \
    { \
        typedef ::cppcms_boost::iostreams::detail::pipeline_segment< \
                    filter CPPCMS_BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T) \
                > segment; \
        return ::cppcms_boost::iostreams::pipeline<segment, Component> \
                   (segment(f), c); \
    } \
    /**/

namespace cppcms_boost { namespace iostreams {

template<typename Pipeline, typename Component>
struct pipeline;
    
namespace detail {

#if CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_MSVC, <= 1300) 
    struct pipeline_base { };

    template<typename T>
    struct is_pipeline 
        : is_base_and_derived<pipeline_base, T>
        { };
#endif 
#if CPPCMS_BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    template<typename T>
    struct is_pipeline : mpl::false_ { };

    template<typename Pipeline, typename Component>
    struct is_pipeline< pipeline<Pipeline, Component> > : mpl::true_ { };
#endif

template<typename Component>
class pipeline_segment 
#if CPPCMS_BOOST_WORKAROUND(CPPCMS_BOOST_MSVC, <= 1300)
    : pipeline_base 
#endif 
{
public:
    pipeline_segment(const Component& component) 
        : component_(component) 
        { }
    template<typename Fn>
    void for_each(Fn fn) const { fn(component_); }
    template<typename Chain>
    void push(Chain& chn) const { chn.push(component_); }
private:
    pipeline_segment operator=(const pipeline_segment&);
    const Component& component_;
};

} // End namespace detail.
                    
//------------------Definition of Pipeline------------------------------------//

template<typename Pipeline, typename Component>
struct pipeline : Pipeline {
    typedef Pipeline   pipeline_type;
    typedef Component  component_type;
    pipeline(const Pipeline& p, const Component& component)
        : Pipeline(p), component_(component)
        { }
    template<typename Fn>
    void for_each(Fn fn) const
    {
        Pipeline::for_each(fn);
        fn(component_);
    }
    template<typename Chain>
    void push(Chain& chn) const
    { 
        Pipeline::push(chn);
        chn.push(component_);
    }
    const Pipeline& tail() const { return *this; }
    const Component& head() const { return component_; }
private:
    pipeline operator=(const pipeline&);
    const Component& component_;
};

template<typename Pipeline, typename Filter, typename Component>
pipeline<pipeline<Pipeline, Filter>, Component>
operator|(const pipeline<Pipeline, Filter>& p, const Component& cmp)
{
    CPPCMS_BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    return pipeline<pipeline<Pipeline, Filter>, Component>(p, cmp);
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_PIPABLE_HPP_INCLUDED
