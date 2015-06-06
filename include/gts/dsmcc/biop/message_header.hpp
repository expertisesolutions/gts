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

#ifndef GTS_DSMCC_BIOP_MESSAGE_HEADER_HPP
#define GTS_DSMCC_BIOP_MESSAGE_HEADER_HPP

#include <gts/static_offset_size_iterator.hpp>

#include <boost/mpl/size_t.hpp>

#include <boost/integer.hpp>

namespace gts { namespace dsmcc { namespace biop {

namespace message_header_iterators {

template <typename BaseIterator>
struct magic_iterator;

template <typename BaseIterator>
struct biop_version_iterator;

template <typename BaseIterator>
struct byte_order_iterator;

template <typename BaseIterator>
struct message_type_iterator;

template <typename BaseIterator>
struct message_size_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 309
template <typename BaseIterator>
struct message_header
{
  typedef message_header_iterators::magic_iterator<BaseIterator> magic_iterator;
  typedef magic_iterator begin_iterator;
  typedef message_header_iterators::biop_version_iterator<BaseIterator> biop_version_iterator;
  typedef message_header_iterators::byte_order_iterator<BaseIterator> byte_order_iterator;
  typedef message_header_iterators::message_type_iterator<BaseIterator> message_type_iterator;
  typedef message_header_iterators::message_size_iterator<BaseIterator> message_size_iterator;
  typedef message_header_iterators::end_iterator<BaseIterator> end_iterator;

  typedef BaseIterator base_iterator;
  message_header(base_iterator first, base_iterator last)
    : first(first), last(last) {}

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  base_iterator first, last;
};

namespace message_header_iterators {

template <typename BaseIterator>
struct magic_iterator : static_offset_size_iterator
<magic_iterator<BaseIterator>, BaseIterator, message_header<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
 , biop_version_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  magic_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct biop_version_iterator : static_offset_size_iterator
<biop_version_iterator<BaseIterator>, BaseIterator, message_header<BaseIterator>
 , boost::mpl::size_t<32u>, boost::mpl::size_t<16u>, boost::uint_t<16u>::least
 , byte_order_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  biop_version_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct byte_order_iterator : static_offset_size_iterator
<byte_order_iterator<BaseIterator>, BaseIterator, message_header<BaseIterator>
 , boost::mpl::size_t<48u>, boost::mpl::size_t<8u>, unsigned char
 , message_type_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  byte_order_iterator(sequence_type const& sequence)
    : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct message_type_iterator : static_offset_size_iterator
<message_type_iterator<BaseIterator>, BaseIterator, message_header<BaseIterator>
 , boost::mpl::size_t<56u>, boost::mpl::size_t<8u>, unsigned char
 , message_size_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  message_type_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct message_size_iterator : static_offset_size_iterator
<message_size_iterator<BaseIterator>, BaseIterator, message_header<BaseIterator>
 , boost::mpl::size_t<64u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
 , end_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  message_size_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef message_header<BaseIterator> sequence_type;
  typedef BaseIterator base_iterator;
  typedef boost::mpl::size_t<96u> offset_bits;

  end_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  base_iterator base() const
  {
    return gts::algorithm::position<offset_bits::value>(sequence.first);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
inline bool operator==(magic_iterator<BaseIterator>const& lhs
                       , end_iterator<BaseIterator>const& rhs)
{
  return std::distance(lhs.sequence.base_begin(), lhs.sequence.base_end())
    < magic_iterator<BaseIterator>::bits_offset::value/CHAR_BIT;
}

}

template <typename BaseIterator>
typename message_header<BaseIterator>::begin_iterator message_header<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename message_header<BaseIterator>::end_iterator message_header<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
