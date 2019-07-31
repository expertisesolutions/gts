///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_ITERATOR_TAG_HPP
#define GTS_ITERATORS_ITERATOR_TAG_HPP

namespace gts { namespace iterators {

struct stationary_iterator_tag {};
struct forward_iterator_tag : stationary_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};

template <typename Iterator, typename Enable = void>
struct iterator_tag
{
  typedef typename Iterator::iterator_tag type;
};

} }

#endif

