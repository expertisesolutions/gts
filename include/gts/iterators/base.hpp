///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_BASE_HPP
#define GTS_ITERATORS_BASE_HPP

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct base
{
  typedef typename Iterator::base_type type;
};

}

template <typename Iterator, typename Enable = void>
struct base_impl
{
  static typename iterators::result_of::base<Iterator>::type
  run(Iterator const& iterator)
  {
    return iterator.base();
  }
};

template <typename Iterator>
typename result_of::base<Iterator>::type base(Iterator const& iterator)
{
  return base_impl<Iterator>::run(iterator);
}

} }

#endif
