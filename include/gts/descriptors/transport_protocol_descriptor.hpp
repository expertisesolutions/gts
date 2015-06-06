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

#ifndef GTS_DESCRIPTORS_TRANSPORT_PROTOCOL_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_TRANSPORT_PROTOCOL_DESCRIPTOR_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/descriptors/tagged_descriptor.hpp>
#include <gts/static_offset_size_iterator.hpp>
#include <gts/adaptation_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace descriptors {

namespace transport_protocol_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct protocol_id_iterator;

template <typename BaseIterator>
struct transport_protocol_label_iterator;

template <typename BaseIterator>
struct selector_byte_iterator;

template <typename BaseIterator>
struct end_iterator;

}

namespace transport_protocol_descriptor_detail {

namespace object_carousel_transport_detail {

template <typename BaseIterator>
struct optional_remote_part
{
  
};

}

namespace object_carousel_transport_iterators {

template <typename BaseIterator>
struct remote_connection_iterator;

template <typename BaseIterator>
struct original_network_id_iterator;

template <typename BaseIterator>
struct transport_stream_id_iterator;

template <typename BaseIterator>
struct service_id_iterator;

template <typename BaseIterator>
struct component_tag_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct object_carousel_transport
{
  typedef object_carousel_transport_iterators::remote_connection_iterator<BaseIterator>
    remote_connection_iterator;
  typedef remote_connection_iterator begin_iterator;
  typedef object_carousel_transport_iterators::original_network_id_iterator<BaseIterator>
    original_network_id_iterator;
  typedef object_carousel_transport_iterators::transport_stream_id_iterator<BaseIterator>
    transport_stream_id_iterator;
  typedef object_carousel_transport_iterators::service_id_iterator<BaseIterator>
    service_id_iterator;
  typedef object_carousel_transport_iterators::component_tag_iterator<BaseIterator>
    component_tag_iterator;
  typedef object_carousel_transport_iterators::end_iterator<BaseIterator> end_iterator;

  typedef BaseIterator base_iterator;

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  object_carousel_transport(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}
  object_carousel_transport(boost::iterator_range<BaseIterator> range)
    : first(boost::begin(range)), last(boost::end(range)) {}

  BaseIterator first, last;
};

namespace object_carousel_transport_iterators {

struct size_comparable {};
struct offset_comparable {};

template <typename BaseIterator>
struct remote_connection_iterator : static_offset_size_iterator
<remote_connection_iterator<BaseIterator>, BaseIterator
 , object_carousel_transport<BaseIterator>, boost::mpl::size_t<0u>
 , boost::mpl::size_t<1u>, bool
 , original_network_id_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef object_carousel_transport<BaseIterator> sequence_type;

  remote_connection_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct original_network_id_iterator : static_offset_size_iterator
<original_network_id_iterator<BaseIterator>, BaseIterator
 , object_carousel_transport<BaseIterator>, boost::mpl::size_t<8u>
 , boost::mpl::size_t<16u>, unsigned int
 , transport_stream_id_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef object_carousel_transport<BaseIterator> sequence_type;

  original_network_id_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct transport_stream_id_iterator : static_offset_size_iterator
<transport_stream_id_iterator<BaseIterator>, BaseIterator
 , object_carousel_transport<BaseIterator>, boost::mpl::size_t<24u>
 , boost::mpl::size_t<16u>, unsigned int
 , service_id_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef object_carousel_transport<BaseIterator> sequence_type;

  transport_stream_id_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct service_id_iterator : static_offset_size_iterator
<service_id_iterator<BaseIterator>, BaseIterator
 , object_carousel_transport<BaseIterator>, boost::mpl::size_t<40u>
 , boost::mpl::size_t<16u>, unsigned int
 , component_tag_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef object_carousel_transport<BaseIterator> sequence_type;

  service_id_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct component_tag_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef object_carousel_transport<BaseIterator> sequence_type;
  typedef unsigned int deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef boost::mpl::size_t<56u> with_remote_bits_offset;
  typedef boost::mpl::size_t<8u> without_remote_bits_offset;
  
  component_tag_iterator(sequence_type const& sequence)
  : sequence(sequence)
  {}

  base_type base() const
  {
    unsigned int const offset = *sequence.begin() == 1
      ?with_remote_bits_offset::value/CHAR_BIT
      :without_remote_bits_offset::value/CHAR_BIT;
    return boost::next(sequence.base_begin(), offset);
  }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, 0u, bits_size::value>
      (base());
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename object_carousel_transport<BaseIterator>::begin_iterator
object_carousel_transport<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

}

// Defined in ETSI 102 809 v1.1.1 (2010-01) page 41
template <typename BaseIterator>
struct transport_protocol_descriptor : tagged_descriptor<BaseIterator>
{
  typedef tagged_descriptor<BaseIterator> base_type;
  typedef transport_protocol_descriptor_iterators::tag_iterator<BaseIterator>
    tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef transport_protocol_descriptor_iterators::protocol_id_iterator<BaseIterator>
    protocol_id_iterator;
  typedef transport_protocol_descriptor_iterators::transport_protocol_label_iterator<BaseIterator>
    transport_protocol_label_iterator;
  typedef transport_protocol_descriptor_iterators::selector_byte_iterator<BaseIterator>
    selector_byte_iterator;
  typedef transport_protocol_descriptor_iterators::end_iterator<BaseIterator>
    end_iterator;

  typedef transport_protocol_descriptor_detail::object_carousel_transport<BaseIterator> object_carousel_transport;
  
  begin_iterator begin() const;
  end_iterator end() const;

  transport_protocol_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  transport_protocol_descriptor(base_type base)
    : base_type(base) {}
};

namespace transport_protocol_descriptor_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , transport_protocol_descriptor<BaseIterator>
                        , typename transport_protocol_descriptor<BaseIterator>
                          ::protocol_id_iterator
                        >
  , offset_comparable, size_comparable
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef transport_protocol_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , transport_protocol_descriptor<BaseIterator>
                              , typename transport_protocol_descriptor<BaseIterator>
                                ::protocol_id_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct protocol_id_iterator : static_offset_size_iterator
<protocol_id_iterator<BaseIterator>, BaseIterator
 , transport_protocol_descriptor<BaseIterator>, boost::mpl::size_t<16u>
 , boost::mpl::size_t<16u>, unsigned int
 , transport_protocol_label_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef transport_protocol_descriptor<BaseIterator> sequence_type;

  protocol_id_iterator
  (sequence_type const& sequence
   , typename tagged_descriptor<BaseIterator>::data_iterator)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct transport_protocol_label_iterator : static_offset_size_iterator
<transport_protocol_label_iterator<BaseIterator>, BaseIterator
 , transport_protocol_descriptor<BaseIterator>, boost::mpl::size_t<32u>
 , boost::mpl::size_t<8u>, unsigned int
 , selector_byte_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef transport_protocol_descriptor<BaseIterator> sequence_type;

  transport_protocol_label_iterator (sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct selector_byte_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<40u> bits_offset;
  typedef transport_protocol_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;

  selector_byte_iterator(sequence_type const& sequence)
  : sequence(sequence) {}

  base_type base() const
  {
    return algorithm::position<bits_offset::value>
      (sequence.base_begin());
  }
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename transport_protocol_descriptor<BaseIterator>::begin_iterator
transport_protocol_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} }

#endif

