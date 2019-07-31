///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DOWNLOAD_DATA_BLOCK_HPP
#define GTS_DSMCC_DOWNLOAD_DATA_BLOCK_HPP

#include <gts/dsmcc/message_header.hpp>
#include <gts/dsmcc/user_network_message.hpp>
#include <gts/adaptation_iterator.hpp>

namespace gts { namespace dsmcc {

namespace download_data_block_iterators {

template <typename BaseIterator>
struct download_data_block_internal_sequence
{
  typedef BaseIterator base_iterator;
  download_data_block_internal_sequence(base_iterator first, base_iterator last)
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
struct download_id_iterator;

template <typename BaseIterator>
struct adaptation_iterator;

template <typename BaseIterator>
struct module_id_iterator;

template <typename BaseIterator>
struct module_version_iterator;

template <typename BaseIterator>
struct block_number_iterator;

template <typename BaseIterator>
struct block_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 259
template <typename BaseIterator>
struct download_data_block
{
  typedef download_data_block_iterators::protocol_discriminator_iterator<BaseIterator>
    protocol_discriminator_iterator;
  typedef protocol_discriminator_iterator begin_iterator;
  typedef download_data_block_iterators::dsmcc_type_iterator<BaseIterator>
    dsmcc_type_iterator;
  typedef download_data_block_iterators::message_id_iterator<BaseIterator>
    message_id_iterator;
  typedef download_data_block_iterators::download_id_iterator<BaseIterator>
    download_id_iterator;
  typedef download_data_block_iterators::adaptation_iterator<BaseIterator>
    adaptation_iterator;
  typedef download_data_block_iterators::module_id_iterator<BaseIterator> module_id_iterator;
  typedef download_data_block_iterators::module_version_iterator<BaseIterator> module_version_iterator;
  typedef download_data_block_iterators::block_number_iterator<BaseIterator> block_number_iterator;
  typedef download_data_block_iterators::block_data_iterator<BaseIterator> block_data_iterator;
  typedef download_data_block_iterators::end_iterator<BaseIterator> end_iterator;

  typedef message_header<BaseIterator> base_type;

  typedef BaseIterator base_iterator;
  download_data_block (base_iterator first, base_iterator last)
    : base_message(first, last) {}
  download_data_block (base_type base_message)
    : base_message(base_message) {}
  download_data_block (user_network_message<BaseIterator> const& un)
    : base_message(un.base_begin (), un.base_end ()) {}

  begin_iterator begin () const;
  end_iterator end () const;

  base_iterator base_begin () const { return base_message.base_begin (); }
  base_iterator base_end () const { return base_message.base_end (); }
  
  base_type base_message;
};

namespace download_data_block_iterators {

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
   , download_data_block<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
    <typename dsmcc::message_header<BaseIterator>::protocol_discriminator_iterator
     , download_data_block<BaseIterator>
     , dsmcc_type_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  protocol_discriminator_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct dsmcc_type_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::dsmcc_type_iterator
   , download_data_block<BaseIterator>
   , message_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::dsmcc_type_iterator
   , download_data_block<BaseIterator>
   , message_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  dsmcc_type_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct message_id_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::message_id_iterator
   , download_data_block<BaseIterator>
   , download_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::message_id_iterator
   , download_data_block<BaseIterator>
   , download_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  message_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct download_id_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::transaction_id_iterator
   , download_data_block<BaseIterator>
   , adaptation_iterator<BaseIterator>
   , void, customizable_increments_next_iterator<adaptation_iterator<BaseIterator>, 3> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::transaction_id_iterator
   , download_data_block<BaseIterator>
   , adaptation_iterator<BaseIterator>
   , void, customizable_increments_next_iterator<adaptation_iterator<BaseIterator>, 3> >
   adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  download_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct adaptation_iterator : gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::adaptation_iterator
   , download_data_block<BaseIterator>
   , module_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename dsmcc::message_header<BaseIterator>::adaptation_iterator
   , download_data_block<BaseIterator>
   , module_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  adaptation_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct module_id_iterator : static_offset_size_iterator
  <module_id_iterator<BaseIterator>, BaseIterator
   , download_data_block_internal_sequence<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<16u>, unsigned int
   , module_version_iterator<BaseIterator> >
{
  typedef download_data_block_internal_sequence<BaseIterator> sequence_type;
  typedef download_data_block<BaseIterator> outside_sequence_type;
  typedef message_header<BaseIterator> message_header_type;

  module_id_iterator(outside_sequence_type const& outside_sequence
                     , typename message_header_type::end_iterator end)
    : sequence(end.base (), outside_sequence.base_end ()) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct module_version_iterator : static_offset_size_iterator
  <module_version_iterator<BaseIterator>, BaseIterator
   , download_data_block_internal_sequence<BaseIterator>
   , boost::mpl::size_t<16u>, boost::mpl::size_t<8u>, unsigned int
   , block_number_iterator<BaseIterator> >
{
  typedef download_data_block_internal_sequence<BaseIterator> sequence_type;
  
  module_version_iterator(sequence_type sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct block_number_iterator : static_offset_size_iterator
  <block_number_iterator<BaseIterator>, BaseIterator
   , download_data_block_internal_sequence<BaseIterator>
   , boost::mpl::size_t<32u>, boost::mpl::size_t<16u>, unsigned int
   , block_data_iterator<BaseIterator> >
{
  typedef download_data_block_internal_sequence<BaseIterator> sequence_type;

  block_number_iterator(sequence_type sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct block_data_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  typedef download_data_block_internal_sequence<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef boost::mpl::size_t<48u> offset_bits;
  
  block_data_iterator(sequence_type sequence)
    : sequence(sequence) {}

  base_type base() const
  {
    return algorithm::position<offset_bits::value>(sequence.base_begin());
  }
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename download_data_block<BaseIterator>::begin_iterator
download_data_block<BaseIterator>::begin () const
{
  return begin_iterator(*this, base_message.begin ());
}

} }

#endif
