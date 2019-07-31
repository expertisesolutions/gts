///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_STATIC_OFFSET_SIZE_ITERATOR_HPP
#define GTS_STATIC_OFFSET_SIZE_ITERATOR_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

namespace gts {

template <typename Derived, typename BaseIterator, typename Sequence, typename BitsOffset, typename BitsSize
          , typename Deref, typename Next>
struct static_offset_size_iterator
{
  typedef BaseIterator base_type;
  typedef Sequence sequence_type;
  typedef BitsOffset bits_offset;
  typedef BitsSize bits_size;
  typedef Deref deref_type;
  typedef Next next_type;

  Derived& this_ () { return static_cast<Derived&>(*this); }
  Derived const& this_ () const { return static_cast<Derived const&>(*this); }

  typedef iterators::forward_iterator_tag iterator_tag;
  base_type base() const
  { return algorithm::position<bits_offset::value>
      (this_ ().sequence.base_begin ());
  }
  deref_type operator*() const
  {
    return algorithm::parse_data
      <deref_type, bits_offset::value, bits_size::value>
      (this_ ().sequence.base_begin ());
  }
  next_type operator++() const
  {
    return typename Derived::next_type(this_ ().sequence);
  }
};

}

#endif
