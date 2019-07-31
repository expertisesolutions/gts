///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_ALGORITHM_FOR_EACH_HPP
#define GTS_ITERATORS_ALGORITHM_FOR_EACH_HPP

#include <gts/iterators/next.hpp>

namespace gts { namespace iterators { namespace algorithm {

namespace for_each_detail {

template <typename First, typename Last, typename F>
inline void for_each(First const&, Last const&, F const&, boost::mpl::true_)
{
}

template <typename First, typename Last, typename F>
inline void for_each(First first, Last last, F f, boost::mpl::false_)
{
  if(first != last)
  {
    f(*first);
    for_each_detail::for_each(++first, last, f
                              , typename boost::is_same
                              <typename iterators::result_of::next<First>::type
                               , Last>::type());
  }
}

}

template <typename First, typename Last, typename F>
void for_each(First first, Last last, F f)
{
  return for_each_detail::for_each(first, last, f
                                   , typename boost::is_same<First, Last>::type());
}

} } }

#endif
