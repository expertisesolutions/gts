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

#ifndef GTS_DSMCC_USER_NETWORK_MESSAGE_HPP
#define GTS_DSMCC_USER_NETWORK_MESSAGE_HPP

#include <gts/dsmcc/message_header.hpp>
#include <gts/adaptation_iterator.hpp>

namespace gts { namespace dsmcc {

namespace user_network_message_iterators {

template <typename BaseIterator>
struct protocol_discriminator_iterator;

template <typename BaseIterator>
struct dsmcc_type_iterator_tag;

template <typename BaseIterator>
struct dsmcc_type_iterator;

template <typename BaseIterator>
struct message_id_iterator_tag;

template <typename BaseIterator>
struct message_id_iterator;

template <typename BaseIterator>
struct transaction_id_iterator;

template <typename BaseIterator>
struct adaptation_iterator;

template <typename BaseIterator>
struct message_payload_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 19
template <typename BaseIterator>
struct user_network_message
{
  typedef dsmcc::message_header<BaseIterator> base_type;
  typedef BaseIterator base_iterator;

  typedef user_network_message_iterators::protocol_discriminator_iterator<BaseIterator>
    protocol_discriminator_iterator;
  typedef protocol_discriminator_iterator begin_iterator;
  typedef user_network_message_iterators::dsmcc_type_iterator<BaseIterator>
    dsmcc_type_iterator;
  typedef user_network_message_iterators::message_id_iterator<BaseIterator>
    message_id_iterator;
  typedef user_network_message_iterators::transaction_id_iterator<BaseIterator>
    transaction_id_iterator;
  typedef user_network_message_iterators::adaptation_iterator<BaseIterator>
    adaptation_iterator;
  typedef user_network_message_iterators::message_payload_iterator<BaseIterator>
    message_payload_iterator;
  typedef user_network_message_iterators::end_iterator<BaseIterator> end_iterator;

  user_network_message(BaseIterator first, BaseIterator last)
    : base_message(first, last) {}

  base_iterator base_begin () const { return base_message.base_begin (); }
  base_iterator base_end () const { return base_message.base_end (); }

  base_type base_message;

  begin_iterator begin () const;
  end_iterator end () const;
};

namespace user_network_message_iterators {

template <typename NextIterator, int I>
struct customizable_increments_next_iterator
{
  typedef NextIterator result_type;
  template <typename Sequence, typename CurrentAdapted>
  NextIterator operator()(Sequence const& sequence, CurrentAdapted const& current_adapted) const
  {
    return NextIterator(sequence, gts::iterators::next<I>(current_adapted));
  }
};

template <typename BaseIterator>
struct protocol_discriminator_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::protocol_discriminator_iterator
   , user_network_message<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
    <typename dsmcc::message_header<BaseIterator>::protocol_discriminator_iterator
     , user_network_message<BaseIterator>
     , dsmcc_type_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  protocol_discriminator_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct dsmcc_type_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::dsmcc_type_iterator
   , user_network_message<BaseIterator>
   , message_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::dsmcc_type_iterator
   , user_network_message<BaseIterator>
   , message_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  dsmcc_type_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct message_id_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::message_id_iterator
   , user_network_message<BaseIterator>
   , transaction_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::message_id_iterator
   , user_network_message<BaseIterator>
   , transaction_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  message_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct transaction_id_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::transaction_id_iterator
   , user_network_message<BaseIterator>
   , adaptation_iterator<BaseIterator>
   , void, customizable_increments_next_iterator<adaptation_iterator<BaseIterator>, 3> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::transaction_id_iterator
   , user_network_message<BaseIterator>
   , adaptation_iterator<BaseIterator>
   , void, customizable_increments_next_iterator<adaptation_iterator<BaseIterator>, 3> >
   adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  transaction_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct adaptation_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::adaptation_iterator
   , user_network_message<BaseIterator>
   , message_payload_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::adaptation_iterator
   , user_network_message<BaseIterator>
   , message_payload_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  adaptation_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct message_payload_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  typedef user_network_message<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;

  message_payload_iterator(sequence_type const& sequence
                           , typename message_header<BaseIterator>::end_iterator end)
    : sequence(sequence), payload_offset(end.base ())
  {}

  base_type base() const { return payload_offset; }
  
  deref_type operator*() const
  {
    return deref_type(payload_offset, sequence.base_message.last);
  }

  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(*this);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename user_network_message<BaseIterator>::begin_iterator
user_network_message<BaseIterator>::begin () const
{
  return begin_iterator(*this, base_message.begin ());
}

} }

#endif
