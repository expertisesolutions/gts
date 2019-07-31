///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_DEREF_HPP
#define GTS_ITERATORS_DEREF_HPP

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct deref
{
  typedef typename Iterator::deref_type type;
};

}

template <typename Iterator, typename Enable = void>
struct deref_impl
{
  static typename iterators::result_of::deref<Iterator>::type
  run(Iterator const& iterator)
  {
    return *iterator;
  }
};

template <typename Iterator>
typename iterators::result_of::deref<Iterator>::type deref(Iterator const& iterator)
{
  return iterators::deref_impl<Iterator>::run(iterator);
}

} }

#endif
