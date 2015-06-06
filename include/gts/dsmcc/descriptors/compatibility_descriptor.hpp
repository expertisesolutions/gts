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

#ifndef GTS_DSMCC_DESCRIPTORS_COMPATIBILITY_DESCRIPTOR_HPP
#define GTS_DSMCC_DESCRIPTORS_COMPATIBILITY_DESCRIPTOR_HPP

#include <gts/static_offset_size_iterator.hpp>

namespace gts { namespace dsmcc { namespace descriptors {

namespace compatibility_descriptor_iterators {

template <typename BaseIterator>
struct descriptor_length_iterator;

template <typename BaseIterator>
struct descriptor_count_iterator;

template <typename BaseIterator>
struct compatibility_descriptor_range_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct compatibility_descriptor_range;

// Defined in ISO IEC 13818-6:1998 page 249
template <typename BaseIterator>
struct compatibility_descriptor
{
  typedef compatibility_descriptor_iterators::descriptor_length_iterator<BaseIterator>
    descriptor_length_iterator;
  typedef descriptor_length_iterator begin_iterator;
  typedef compatibility_descriptor_iterators::descriptor_count_iterator<BaseIterator>
    descriptor_count_iterator;
  typedef compatibility_descriptor_iterators::compatibility_descriptor_range_iterator<BaseIterator>
    compatibility_descriptor_range_iterator;
  typedef compatibility_descriptor_iterators::end_iterator<BaseIterator> end_iterator;

  compatibility_descriptor(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {
  }

  typedef BaseIterator base_iterator;
  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  begin_iterator begin () const;
  end_iterator end () const;

  base_iterator first, last;
};

namespace compatibility_descriptor_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct descriptor_length_iterator : static_offset_size_iterator
  <descriptor_length_iterator<BaseIterator>, BaseIterator
   , compatibility_descriptor<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<16u>, unsigned int
   , descriptor_count_iterator<BaseIterator> >
{
  typedef compatibility_descriptor<BaseIterator> sequence_type;

  descriptor_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct descriptor_count_iterator : static_offset_size_iterator
  <descriptor_count_iterator<BaseIterator>, BaseIterator
   , compatibility_descriptor<BaseIterator>
   , boost::mpl::size_t<16u>, boost::mpl::size_t<16u>, unsigned int
   , compatibility_descriptor_range_iterator<BaseIterator> >
{
  typedef compatibility_descriptor<BaseIterator> sequence_type;

  descriptor_count_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

}

template <typename BaseIterator>
typename compatibility_descriptor<BaseIterator>::begin_iterator
compatibility_descriptor<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

} } }

#endif
