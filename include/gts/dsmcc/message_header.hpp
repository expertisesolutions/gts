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

#ifndef GTS_DSMCC_MESSAGE_HEADER_HPP
#define GTS_DSMCC_MESSAGE_HEADER_HPP

#include <gts/static_offset_size_iterator.hpp>
#include <boost/range/iterator_range.hpp>

#include <iostream>

namespace gts { namespace dsmcc {

namespace message_header_iterators {

template <typename BaseIterator>
struct protocol_discriminator_iterator;

template <typename BaseIterator>
struct dsmcc_type_iterator;

template <typename BaseIterator>
struct message_id_iterator;

template <typename BaseIterator>
struct transaction_id_iterator;

template <typename BaseIterator>
struct adaptation_length_iterator;

template <typename BaseIterator>
struct message_length_iterator;

template <typename BaseIterator>
struct adaptation_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct adaptation_header
{
  adaptation_header (BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;
  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  bool empty () { return first == last; }

  unsigned int type () const
  {
    return algorithm::parse_data<unsigned int, 0u, 8u> (first);
  }

  boost::iterator_range<BaseIterator> data () const
  {
    return boost::iterator_range<BaseIterator>(boost::next(first), last);
  }

  BaseIterator first, last;
};

// Defined in ISO IEC 13818-6:1998 page 7
template <typename BaseIterator>
struct message_header
{
  typedef message_header_iterators::protocol_discriminator_iterator<BaseIterator>
    protocol_discriminator_iterator;
  typedef protocol_discriminator_iterator begin_iterator;
  typedef message_header_iterators::dsmcc_type_iterator<BaseIterator> dsmcc_type_iterator;
  typedef message_header_iterators::message_id_iterator<BaseIterator> message_id_iterator;
  typedef message_header_iterators::transaction_id_iterator<BaseIterator> transaction_id_iterator;
  typedef message_header_iterators::adaptation_length_iterator<BaseIterator> adaptation_length_iterator;
  typedef message_header_iterators::message_length_iterator<BaseIterator> message_length_iterator;
  typedef message_header_iterators::adaptation_iterator<BaseIterator> adaptation_iterator;
  typedef message_header_iterators::end_iterator<BaseIterator> end_iterator;

  message_header(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  begin_iterator begin () const;
  end_iterator end () const;

  typedef BaseIterator base_iterator;

  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  base_iterator first, last;
};

namespace message_header_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct protocol_discriminator_iterator : static_offset_size_iterator
<protocol_discriminator_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<8u>, unsigned int
 , dsmcc_type_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  protocol_discriminator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}
  
  sequence_type const& sequence;
};

template <typename BaseIterator>
struct dsmcc_type_iterator : static_offset_size_iterator
<dsmcc_type_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<8u>, boost::mpl::size_t<8u>, unsigned int
 , message_id_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  dsmcc_type_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct message_id_iterator : static_offset_size_iterator
<message_id_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<16u>, boost::mpl::size_t<16u>, unsigned int
 , transaction_id_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  message_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct transaction_id_iterator : static_offset_size_iterator
<transaction_id_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<32u>, boost::mpl::size_t<32u>, unsigned int
 , adaptation_length_iterator<BaseIterator> >
{
  typedef message_header<BaseIterator> sequence_type;

  transaction_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct adaptation_length_iterator : static_offset_size_iterator
<adaptation_length_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<72u>, boost::mpl::size_t<8u>, unsigned int
 , void>
{
  typedef message_header<BaseIterator> sequence_type;

  adaptation_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef message_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, **this);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct message_length_iterator : static_offset_size_iterator
<message_length_iterator<BaseIterator>, BaseIterator
 , message_header<BaseIterator>
 , boost::mpl::size_t<80u>, boost::mpl::size_t<16u>, unsigned int
 , void>
{
  typedef message_header<BaseIterator> sequence_type;
  typedef adaptation_length_iterator<BaseIterator> prior_type;
  typedef typename prior_type::deref_type adaptation_length_type;

  message_length_iterator(sequence_type const& sequence
                          , adaptation_length_type adaptation_length)
    : sequence(sequence), adaptation_length(adaptation_length) {}

  typedef adaptation_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, adaptation_length, **this);
  }
  
  sequence_type const& sequence;
  adaptation_length_type adaptation_length;
};

template <typename BaseIterator>
struct adaptation_iterator
{
  typedef boost::mpl::size_t<96u> bits_offset;
  typedef adaptation_header<BaseIterator> deref_type;
  typedef BaseIterator base_type;
  typedef message_header<BaseIterator> sequence_type;
  typedef iterators::forward_iterator_tag iterator_tag;

  typedef message_header_iterators::adaptation_length_iterator<BaseIterator> adaptation_length_iterator;
  typedef typename adaptation_length_iterator::deref_type adaptation_length_type;
  typedef message_header_iterators::message_length_iterator<BaseIterator> message_length_iterator;
  typedef typename message_length_iterator::deref_type message_length_type;

  adaptation_iterator(sequence_type const& sequence
                      , adaptation_length_type adaptation_length
                      , message_length_type message_length)
    : sequence(sequence), adaptation_length(adaptation_length)
    , message_length(message_length) {}


  base_type base() const
  { return algorithm::position<bits_offset::value>(sequence.base_begin ()); }
  deref_type operator*() const
  {
    BaseIterator first = base ();
    return deref_type(first, boost::next(first, adaptation_length));
  }

  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, adaptation_length, message_length);
  }
  
  sequence_type const& sequence;
  adaptation_length_type adaptation_length;
  message_length_type message_length;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef BaseIterator base_type;
  typedef iterators::stationary_iterator_tag iterator_tag;
  typedef message_header<BaseIterator> sequence_type;

  typedef message_header_iterators::adaptation_length_iterator<BaseIterator> adaptation_length_iterator;
  typedef typename adaptation_length_iterator::deref_type adaptation_length_type;
  typedef message_header_iterators::message_length_iterator<BaseIterator> message_length_iterator;
  typedef typename message_length_iterator::deref_type message_length_type;
  
  end_iterator(sequence_type const& sequence
               , adaptation_length_type adaptation_length
               , message_length_type message_length)
    : sequence(sequence), adaptation_length(adaptation_length)
    , message_length(message_length) {}

  base_type base() const
  {
    return boost::next(sequence.first, adaptation_iterator<BaseIterator>::bits_offset::value/CHAR_BIT
                       + adaptation_length);
  }

  sequence_type const& sequence;
  adaptation_length_type adaptation_length;
  message_length_type message_length;
};

}

template <typename BaseIterator>
typename message_header<BaseIterator>::begin_iterator
message_header<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} }

#endif
