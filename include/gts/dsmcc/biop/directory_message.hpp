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

#ifndef GTS_DSMCC_BIOP_DIRECTORY_MESSAGE_HPP
#define GTS_DSMCC_BIOP_DIRECTORY_MESSAGE_HPP

#include <gts/base_sequence.hpp>
#include <gts/dsmcc/biop/binds.hpp>

namespace gts { namespace dsmcc { namespace biop {

namespace directory_message_iterators {

template <typename BaseIterator>
struct message_body_length_iterator;

template <typename BaseIterator>
struct binds_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 311
template <typename BaseIterator>
struct directory_message
{
  typedef directory_message_iterators::message_body_length_iterator<BaseIterator> message_body_length_iterator;
  typedef message_body_length_iterator begin_iterator;
  typedef directory_message_iterators::binds_iterator<BaseIterator> binds_iterator;
  typedef directory_message_iterators::end_iterator<BaseIterator> end_iterator;

  directory_message(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}
  directory_message() : first(), last() {}

  typedef BaseIterator base_iterator;
  
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

template <typename BaseIterator>
bool operator==(directory_message<BaseIterator> const& lhs, directory_message<BaseIterator> const& rhs)
{
  return lhs.first == rhs.first && lhs.last == rhs.last;
}

namespace directory_message_iterators {

template <typename BaseIterator>
struct message_body_length_iterator : static_offset_size_iterator
<message_body_length_iterator<BaseIterator>, BaseIterator, directory_message<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
 , binds_iterator<BaseIterator> >
{
  typedef directory_message<BaseIterator> sequence_type;

  message_body_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct binds_iterator
{
  typedef directory_message<BaseIterator> sequence_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef boost::mpl::size_t<32u> bits_offset;
  typedef biop::binds<BaseIterator> deref_type;

  binds_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef BaseIterator base_iterator;
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  next_type operator++() const;
  base_iterator base() const
  {
    return algorithm::position<bits_offset::value>(sequence.base_begin());
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename directory_message<BaseIterator>::begin_iterator directory_message<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename directory_message<BaseIterator>::end_iterator directory_message<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
