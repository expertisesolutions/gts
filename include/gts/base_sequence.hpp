///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_BASE_SEQUENCE_HPP
#define GTS_BASE_SEQUENCE_HPP

namespace gts {

template <typename BaseIterator>
struct base_sequence
{
  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  base_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  BaseIterator first, last;
};

}

#endif
