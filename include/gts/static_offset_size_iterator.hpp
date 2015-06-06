/* (c) Copyright 2011-2014 Felipe Magno de Almeida
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
