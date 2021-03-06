///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_NEXT_HPP
#define GTS_ITERATORS_NEXT_HPP

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct next
{
  typedef typename Iterator::next_type type;
};

}

template <typename Iterator, typename Enable = void>
struct next_impl
{
  static typename iterators::result_of::next<Iterator>::type
  run(Iterator const& iterator)
  {
    return ++iterator;
  }
};

template <typename Iterator>
typename iterators::result_of::next<Iterator>::type next(Iterator const& iterator)
{
  return next_impl<Iterator>::run(iterator);
}

namespace next_detail {

namespace result_of {

template <int N, typename F, typename A0>
struct transformationN
{
  template <typename D = void>
  struct apply
  {
    template <typename F1, typename T1>
    struct apply_transformationN
    {
      typedef typename boost::mpl::apply0<T1>::type apply_type;
      typedef typename boost::mpl::apply1<F1, apply_type>::type type;
    };

    typedef typename 
    boost::mpl::eval_if_c<N == 1
                          , boost::mpl::apply<F, A0>
                          , apply_transformationN
                            <F, transformationN<N - 1, F, A0> >
                          >::type type;
  };
};

}

template <int N, typename F>
struct transformationN
{
  template <typename A0>
  typename boost::mpl::apply0<result_of::transformationN<N, F, A0> >::type
  operator () (A0 a0) const
  {
    return transformationN<N-1, F>() (F()(a0));
  }
};

template <typename F>
struct transformationN<1, F>
{
  template <typename A0>
  typename boost::mpl::apply0<result_of::transformationN<1, F, A0> >::type
  operator () (A0 a0) const
  {
    return F () (a0);
  }
};

struct call_next_impl
{
  template <typename T>
  struct apply
  {
    typedef typename iterators::result_of::next<T>::type type;
  };

  template <typename A0>
  typename iterators::result_of::next<A0>::type
  operator()(A0 a0) const
  {
    return next_impl<A0>::run(a0);
  }
};

}

template <int N, typename Iterator>
typename boost::mpl::apply0
<next_detail::result_of::transformationN
<N, iterators::result_of::next<boost::mpl::_>
 , Iterator> >::type
next(Iterator const& iterator)
{
  return next_detail::transformationN
    <N, next_detail::call_next_impl>() (iterator);
}

} }

#endif
