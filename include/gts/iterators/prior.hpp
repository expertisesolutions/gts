///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_PRIOR_HPP
#define GTS_ITERATORS_PRIOR_HPP

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct prior
{
  typedef typename Iterator::prior_type type;
};

}

template <typename Iterator, typename Enable = void>
struct prior_impl
{
  static typename iterators::result_of::prior<Iterator>::type
  run(Iterator const& iterator)
  {
    return iterator.prior();
  }
};

template <typename Iterator>
typename iterators::result_of::next<Iterator>::type prior(Iterator const& iterator)
{
  return prior_impl<Iterator>::run(iterator);
}

} }

#endif
