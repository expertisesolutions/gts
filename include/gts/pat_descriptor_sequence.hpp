///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PAT_DESCRIPTOR_SEQUENCE_HPP
#define GTS_PAT_DESCRIPTOR_SEQUENCE_HPP

namespace gts {

template <typename BaseIterator>
struct pat_descriptor_sequence
{
  pat_descriptor_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  BaseIterator first, last;
};

namespace result_of {

template <typename BaseIterator>
struct begin<pat_descriptor_sequence<BaseIterator> >
{
  typedef pat_descriptor_sequence<BaseIterator> self_type;
  typedef typename self_type::
};

}

}

#endif
