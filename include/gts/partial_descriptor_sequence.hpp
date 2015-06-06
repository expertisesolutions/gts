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

#ifndef GTS_PARTIAL_DESCRIPTOR_SEQUENCE_HPP
#define GTS_PARTIAL_DESCRIPTOR_SEQUENCE_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts {

namespace partial_descriptor_iterators {

template <typename BaseIterator>
struct descriptor_tag_iterator;

template <typename BaseIterator>
struct descriptor_length_iterator;

template <typename BaseIterator>
struct descriptor_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct partial_descriptor_sequence
{
  partial_descriptor_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  typedef partial_descriptor_iterators::descriptor_tag_iterator<BaseIterator> descriptor_tag_iterator;
  typedef descriptor_tag_iterator begin_iterator;
  typedef partial_descriptor_iterators::descriptor_length_iterator<BaseIterator> descriptor_length_iterator;
  typedef partial_descriptor_iterators::descriptor_data_iterator<BaseIterator> descriptor_data_iterator;
  typedef partial_descriptor_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;

  BaseIterator first, last;
};

namespace partial_descriptor_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct descriptor_tag_iterator : offset_comparable, size_comparable
{
  typedef partial_descriptor_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;

  descriptor_tag_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef descriptor_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct descriptor_length_iterator : offset_comparable, size_comparable
{
  typedef partial_descriptor_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;

  descriptor_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef descriptor_data_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct descriptor_data_iterator : offset_comparable
{
  typedef partial_descriptor_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<16u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;

  descriptor_data_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return deref_type(boost::next(sequence.first, bits_offset::value/CHAR_BIT)
                      , boost::next(sequence.first, bits_offset::value/CHAR_BIT
                                    + *gts::iterators::next(sequence.begin ())));
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

}

template <typename BaseIterator>
typename partial_descriptor_sequence<BaseIterator>::begin_iterator
partial_descriptor_sequence<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

}

#endif
