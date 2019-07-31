///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DOWNLOAD_SERVER_INITIATE_HPP
#define GTS_DSMCC_DOWNLOAD_SERVER_INITIATE_HPP

#include <gts/dsmcc/descriptors/compatibility_descriptor.hpp>
#include <gts/adaptation_iterator.hpp>
#include <gts/dsmcc/biop/parsers/prefixed_string.hpp>

namespace gts { namespace dsmcc {

namespace download_server_initiate_iterators {

template <typename BaseIterator>
struct download_server_initiate_internal_sequence
{
  typedef BaseIterator base_iterator;
  download_server_initiate_internal_sequence(base_iterator first, base_iterator last)
    : first(first), last(last) {}

  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  base_iterator first, last;
};

template <typename BaseIterator>
struct protocol_discriminator_iterator;

template <typename BaseIterator>
struct dsmcc_type_iterator;

template <typename BaseIterator>
struct message_id_iterator;

template <typename BaseIterator>
struct transaction_id_iterator;

template <typename BaseIterator>
struct adaptation_iterator;

template <typename BaseIterator>
struct server_id_iterator;

template <typename BaseIterator>
struct compatibility_descriptor_iterator;

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct download_server_initiate
{
  typedef BaseIterator base_iterator;

  typedef download_server_initiate_iterators::protocol_discriminator_iterator<BaseIterator>
    protocol_discriminator_iterator;
  typedef protocol_discriminator_iterator begin_iterator;
  typedef download_server_initiate_iterators::dsmcc_type_iterator<BaseIterator> dsmcc_type_iterator;
  typedef download_server_initiate_iterators::message_id_iterator<BaseIterator> message_id_iterator;
  typedef download_server_initiate_iterators::transaction_id_iterator<BaseIterator> transaction_id_iterator;
  typedef download_server_initiate_iterators::adaptation_iterator<BaseIterator> adaptation_iterator;
  typedef download_server_initiate_iterators::server_id_iterator<BaseIterator> server_id_iterator;
  typedef download_server_initiate_iterators::compatibility_descriptor_iterator<BaseIterator>
    compatibility_descriptor_iterator;
  typedef download_server_initiate_iterators::private_data_iterator<BaseIterator> private_data_iterator;
  typedef download_server_initiate_iterators::end_iterator<BaseIterator> end_iterator;

  typedef user_network_message<BaseIterator> base_type;

  download_server_initiate(BaseIterator first, BaseIterator last)
    : base_message(first, last) {}
  download_server_initiate(base_type base_message)
    : base_message(base_message) {}

  begin_iterator begin () const;
  end_iterator end () const;

  base_iterator base_begin () const { return base_message.base_begin (); }
  base_iterator base_end () const { return base_message.base_end (); }

  base_type base_message;
};

namespace download_server_initiate_iterators {

template <typename BaseIterator>
struct protocol_discriminator_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::protocol_discriminator_iterator
   , download_server_initiate<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::protocol_discriminator_iterator
   , download_server_initiate<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  protocol_discriminator_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct dsmcc_type_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::dsmcc_type_iterator
   , download_server_initiate<BaseIterator>
   , message_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::dsmcc_type_iterator
   , download_server_initiate<BaseIterator>
   , message_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  dsmcc_type_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct message_id_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::message_id_iterator
   , download_server_initiate<BaseIterator>
   , transaction_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::message_id_iterator
   , download_server_initiate<BaseIterator>
   , transaction_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  message_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct transaction_id_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::transaction_id_iterator
   , download_server_initiate<BaseIterator>
   , adaptation_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::transaction_id_iterator
   , download_server_initiate<BaseIterator>
   , adaptation_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  transaction_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct adaptation_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::adaptation_iterator
   , download_server_initiate<BaseIterator>
   , server_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::adaptation_iterator
   , download_server_initiate<BaseIterator>
   , server_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  adaptation_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct server_id_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<160u> bits_size;
  typedef download_server_initiate<BaseIterator> outside_sequence_type;
  typedef typename outside_sequence_type::base_type base_sequence_type;
  typedef download_server_initiate_internal_sequence<BaseIterator> sequence_type;
  typedef boost::iterator_range<unsigned char const*> deref_type;

  server_id_iterator(outside_sequence_type const& outside_sequence
                     , typename user_network_message<BaseIterator>::message_payload_iterator payload)
    : sequence(payload.base (), outside_sequence.base_end ())
  {
    assert(payload.base () < outside_sequence.base_end ());
  }

  typedef BaseIterator base_type;
  base_type base () const { return sequence.base_begin (); }

  deref_type operator*() const
  {
    assert(std::distance(sequence.base_begin (), sequence.base_end ()) >= bits_offset::value/CHAR_BIT);
    return deref_type(sequence.base_begin (), boost::next(sequence.base_begin ()));
  }

  typedef compatibility_descriptor_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct compatibility_descriptor_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<160u> bits_offset;
  typedef download_server_initiate_internal_sequence<BaseIterator> sequence_type;
  typedef dsmcc::descriptors::compatibility_descriptor<BaseIterator> deref_type;

  compatibility_descriptor_iterator(sequence_type sequence)
    : sequence(sequence) {}

  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<bits_offset::value>(sequence.base_begin ()); }

  deref_type operator*() const
  {
    deref_type tmp(base(), sequence.base_end());
    assert(*tmp.begin () <= std::distance(base (), sequence.base_end ()));
    return deref_type(base ()
                      , boost::next(base()
                                    , deref_type::descriptor_length_iterator
                                    ::bits_size::value/CHAR_BIT + *tmp.begin ()));
  }

  typedef private_data_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    deref_type tmp(base(), sequence.base_end ());
    return next_type(sequence
                     , boost::next(base ()
                                   , deref_type::descriptor_length_iterator
                                    ::bits_size::value/CHAR_BIT + *tmp.begin ()));
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct private_data_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef download_server_initiate_internal_sequence<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;

  private_data_iterator(sequence_type const& sequence, BaseIterator current)
    : sequence(sequence), current(current) {}

  typedef BaseIterator base_type;
  base_type base() const { return current; }
  deref_type operator*() const
  {
    BaseIterator first = current;
    return dsmcc::biop::parsers::prefixed_string<16u>
      (first, sequence.base_end());
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const;

  sequence_type sequence;
  BaseIterator current;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename download_server_initiate<BaseIterator>::begin_iterator
download_server_initiate<BaseIterator>::begin () const
{
  return begin_iterator(*this, base_message.begin ());
}

template <typename BaseIterator>
typename download_server_initiate<BaseIterator>::end_iterator
download_server_initiate<BaseIterator>::end () const
{
  return end_iterator(*this);
}

} }

#endif
