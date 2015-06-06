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

#ifndef GTS_NIT_PRIVATE_SEQUENCE_HPP
#define GTS_NIT_PRIVATE_SEQUENCE_HPP

#include <gts/partial_descriptor_sequence.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/descriptor_private_range.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts {

namespace nit_private_iterators {

template <typename BaseIterator>
struct network_descriptor1_length_iterator;

template <typename BaseIterator>
struct descriptor1_iterator;

template <typename BaseIterator>
struct transport_stream_loop_length_iterator;

template <typename BaseIterator>
struct transport_stream_identifier_iterator;

template <typename BaseIterator>
struct original_network_identifier_iterator;

template <typename BaseIterator>
struct transport_stream_descriptor2_length_iterator;

template <typename BaseIterator>
struct descriptor_repetition_iterator;

template <typename BaseIterator>
struct crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct nit_private_sequence
{
  nit_private_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef nit_private_iterators::network_descriptor1_length_iterator<BaseIterator>
    network_descriptor1_length_iterator;
  typedef network_descriptor1_length_iterator begin_iterator;
  typedef nit_private_iterators::descriptor1_iterator<BaseIterator> descriptor1_iterator;
  typedef nit_private_iterators::transport_stream_loop_length_iterator<BaseIterator>
    transport_stream_loop_length_iterator;
  typedef nit_private_iterators::transport_stream_identifier_iterator<BaseIterator>
    transport_stream_identifier_iterator;
  typedef nit_private_iterators::original_network_identifier_iterator<BaseIterator>
    original_network_identifier_iterator;
  typedef nit_private_iterators::transport_stream_descriptor2_length_iterator<BaseIterator>
    transport_stream_descriptor2_length_iterator;
  typedef nit_private_iterators::descriptor_repetition_iterator<BaseIterator> descriptor_repetition_iterator;
  typedef nit_private_iterators::crc32_iterator<BaseIterator> crc32_iterator;
  typedef nit_private_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;

  BaseIterator first, last;
};

namespace nit_private_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct network_descriptor1_length_iterator : offset_comparable, size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<4u> bits_offset;
  typedef boost::mpl::size_t<12u> bits_size;
  typedef unsigned int deref_type;

  network_descriptor1_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef descriptor1_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct descriptor1_iterator : offset_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<16u> bits_offset;
  typedef partial_descriptor_sequence<BaseIterator> deref_type;

  descriptor1_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return deref_type(boost::next(sequence.first, bits_offset::value/CHAR_BIT)
                      , boost::next(sequence.first, bits_offset::value/CHAR_BIT
                                    + *sequence.begin ()));
  }
  typedef transport_stream_loop_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence
                     , boost::next(sequence.first, bits_offset::value/CHAR_BIT
                                   + *sequence.begin ()));
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct transport_stream_loop_length_iterator : size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<4u> bits_dynamic_offset;
  typedef boost::mpl::size_t<12u> bits_size;
  typedef unsigned int deref_type;

  transport_stream_loop_length_iterator(sequence_type const& sequence, BaseIterator descriptor1_end)
    : sequence(sequence), descriptor1_end(descriptor1_end) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_dynamic_offset::value>(descriptor1_end); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_dynamic_offset::value, bits_size::value>(descriptor1_end);
  }
  typedef transport_stream_identifier_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, descriptor1_end);
  }

  sequence_type sequence;  
  BaseIterator descriptor1_end;
};

template <typename BaseIterator>
struct transport_stream_identifier_iterator : size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<16u> bits_dynamic_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef unsigned int deref_type;

  transport_stream_identifier_iterator(sequence_type const& sequence, BaseIterator descriptor1_end)
    : sequence(sequence), descriptor1_end(descriptor1_end) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_dynamic_offset::value>(descriptor1_end); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_dynamic_offset::value, bits_size::value>(descriptor1_end);
  }
  typedef original_network_identifier_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, descriptor1_end);
  }

  sequence_type sequence;  
  BaseIterator descriptor1_end;
};

template <typename BaseIterator>
struct original_network_identifier_iterator : size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_dynamic_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef unsigned int deref_type;

  original_network_identifier_iterator(sequence_type const& sequence, BaseIterator descriptor1_end)
    : sequence(sequence), descriptor1_end(descriptor1_end) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_dynamic_offset::value>(descriptor1_end); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_dynamic_offset::value, bits_size::value>(descriptor1_end);
  }
  typedef transport_stream_descriptor2_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, descriptor1_end);
  }

  sequence_type sequence;  
  BaseIterator descriptor1_end;
};

template <typename BaseIterator>
struct transport_stream_descriptor2_length_iterator : size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<52u> bits_dynamic_offset;
  typedef boost::mpl::size_t<12u> bits_size;
  typedef unsigned int deref_type;

  transport_stream_descriptor2_length_iterator(sequence_type const& sequence, BaseIterator descriptor1_end)
    : sequence(sequence), descriptor1_end(descriptor1_end) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_dynamic_offset::value>(descriptor1_end); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_dynamic_offset::value, bits_size::value>(descriptor1_end);
  }
  typedef descriptor_repetition_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, descriptor1_end);
  }

  sequence_type sequence;  
  BaseIterator descriptor1_end;
};

template <typename BaseIterator>
struct descriptor_repetition_iterator
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<64u> bits_dynamic_offset;
  typedef descriptor_private_range<BaseIterator> deref_type;

  descriptor_repetition_iterator(sequence_type const& sequence, BaseIterator descriptor1_end)
    : sequence(sequence), descriptor1_end(descriptor1_end) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_dynamic_offset::value>(descriptor1_end); }
  deref_type operator*() const
  {
    transport_stream_descriptor2_length_iterator<BaseIterator>
      length = gts::iterators::next<5>(sequence.begin ());
    return deref_type(base ()
                      , boost::next(base (), *length));
  }
  typedef crc32_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    transport_stream_descriptor2_length_iterator<BaseIterator>
      length = gts::iterators::next<5>(sequence.begin ());
    return next_type(sequence, boost::next(base (), *length));
  }

  sequence_type sequence;
  BaseIterator descriptor1_end;
};

template <typename BaseIterator>
struct crc32_iterator : size_comparable
{
  typedef nit_private_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef unsigned int deref_type;

  crc32_iterator(sequence_type const& sequence, BaseIterator descriptor_repetition_end)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const;
  deref_type operator*() const;
  // {
  //   return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  // }
  typedef descriptor1_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

}

template <typename BaseIterator>
typename nit_private_sequence<BaseIterator>::begin_iterator nit_private_sequence<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

}

#endif
