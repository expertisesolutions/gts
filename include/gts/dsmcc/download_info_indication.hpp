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

#ifndef GTS_DSMCC_DOWNLOAD_INFO_INDICATION_HPP
#define GTS_DSMCC_DOWNLOAD_INFO_INDICATION_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/dsmcc/user_network_message.hpp>
#include <gts/dsmcc/descriptors/compatibility_descriptor.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace gts { namespace dsmcc {

namespace dii_module_iterators {

template <typename BaseIterator>
struct module_id_iterator;

template <typename BaseIterator>
struct module_size_iterator;

template <typename BaseIterator>
struct module_version_iterator;

template <typename BaseIterator>
struct module_info_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 19
template <typename BaseIterator>
struct dii_module
{
  typedef dii_module_iterators::module_id_iterator<BaseIterator> module_id_iterator;
  typedef module_id_iterator begin_iterator;
  typedef dii_module_iterators::module_size_iterator<BaseIterator> module_size_iterator;
  typedef dii_module_iterators::module_version_iterator<BaseIterator>
    module_version_iterator;
  typedef dii_module_iterators::module_info_iterator<BaseIterator>
    module_info_iterator;
  typedef dii_module_iterators::end_iterator<BaseIterator> end_iterator;

  dii_module (BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;
  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }
  
  begin_iterator begin () const;
  end_iterator end () const;

  BaseIterator first, last;
};

namespace dii_module_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct module_id_iterator : gts::static_offset_size_iterator
  <module_id_iterator<BaseIterator>
   , BaseIterator, dii_module<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<16u>
   , unsigned int, module_size_iterator<BaseIterator> >
  , offset_comparable
  , size_comparable
{
  typedef dii_module<BaseIterator> sequence_type;

  module_id_iterator (sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct module_size_iterator : gts::static_offset_size_iterator
  <module_size_iterator<BaseIterator>
   , BaseIterator, dii_module<BaseIterator>
   , boost::mpl::size_t<16u>, boost::mpl::size_t<32u>
   , unsigned int, module_version_iterator<BaseIterator> >
  , offset_comparable
  , size_comparable
{
  typedef dii_module<BaseIterator> sequence_type;

  module_size_iterator (sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct module_version_iterator : gts::static_offset_size_iterator
  <module_version_iterator<BaseIterator>
   , BaseIterator, dii_module<BaseIterator>
   , boost::mpl::size_t<48u>, boost::mpl::size_t<8u>
   , unsigned int, module_info_iterator<BaseIterator> >
  , offset_comparable
  , size_comparable
{
  typedef dii_module<BaseIterator> sequence_type;

  module_version_iterator (sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct module_info_iterator : offset_comparable
{
  typedef boost::mpl::size_t<56u> info_length_bits_offset;
  typedef boost::mpl::size_t<8u> info_length_bits_size;
  typedef boost::mpl::size_t<64u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef BaseIterator base_type;
  typedef dii_module<BaseIterator> sequence_type;
  typedef iterators::forward_iterator_tag iterator_tag;

  module_info_iterator (sequence_type const& sequence)
    : sequence(sequence) {}

  base_type base() const
  { return algorithm::position<bits_offset::value>(sequence.base_begin ()); }
  deref_type operator*() const
  {
    unsigned int offset_size = algorithm::parse_data
      <unsigned int, info_length_bits_offset::value, info_length_bits_size::value>
      (sequence.base_begin ());
    base_type b = base ();
    return deref_type(b, boost::next(b, (std::min<std::size_t>)
                                     (offset_size
                                      , std::distance(b, sequence.base_end()))));
  }
  
  sequence_type const& sequence;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef BaseIterator base_type;
  typedef iterators::stationary_iterator_tag iterator_tag;
  typedef dii_module<BaseIterator> sequence_type;

  end_iterator(sequence_type const& sequence, BaseIterator last)
    : sequence(sequence), last(last) {}

  base_type base () const { return last; }

  sequence_type const& sequence;
  BaseIterator last;
};

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator> const& lhs
                , end_iterator<BaseIterator> const& rhs)
{
  return true;
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> const& lhs
                , end_iterator<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

template <typename StaticOffsetSizeComparable, typename BaseIterator>
typename boost::enable_if
<typename boost::mpl::and_
 <typename boost::is_convertible<StaticOffsetSizeComparable, offset_comparable>::type
  , typename boost::is_convertible<StaticOffsetSizeComparable, size_comparable>::type
 >::type
, bool>::type
operator==(StaticOffsetSizeComparable const& lhs
           , end_iterator<BaseIterator> const& rhs)
{
  const std::ptrdiff_t offset = StaticOffsetSizeComparable::bits_offset::value/CHAR_BIT;
  const std::ptrdiff_t size = StaticOffsetSizeComparable::bits_size::value/CHAR_BIT;
  return std::distance(lhs.sequence.base_begin (), rhs.base ()) <= offset;
}

template <typename BaseIterator>
bool operator==(module_info_iterator<BaseIterator> const& lhs
                , end_iterator<BaseIterator> const& rhs)
{
  const std::ptrdiff_t offset = module_info_iterator<BaseIterator>::bits_offset::value/CHAR_BIT;
  // minimum size for *lhs is zero. So it is safe
  return std::distance(lhs.sequence.base_begin (), rhs.base ()) <= offset;
}

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator> const& lhs
                , module_info_iterator<BaseIterator> const& rhs)
{
  return rhs == lhs;
}

template <typename StaticOffsetComparable, typename BaseIterator>
typename boost::enable_if
<typename boost::is_convertible
 <StaticOffsetComparable, offset_comparable>::type, bool>::type
operator!=(StaticOffsetComparable const& lhs
           , end_iterator<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

template <typename StaticOffsetComparable, typename BaseIterator>
typename boost::enable_if
<typename boost::is_convertible
 <StaticOffsetComparable, offset_comparable>::type, bool>::type
operator!=(end_iterator<BaseIterator> const& rhs
           , StaticOffsetComparable const& lhs)
{
  return !(lhs == rhs);
}

}

template <typename BaseIterator>
struct dii_module_iterator : boost::iterator_facade<dii_module_iterator<BaseIterator>
                                                    , dii_module<BaseIterator>
                                                    , boost::forward_traversal_tag
                                                    , dii_module<BaseIterator> >
{
  dii_module_iterator (BaseIterator iterator, BaseIterator last
                       , unsigned int modules)
    : base_iterator(iterator), last(last), modules(modules) {}

  bool equal (dii_module_iterator const& other) const
  {
    return other.modules == modules
      || base_iterator == other.base_iterator;
  }
  void increment ()
  {
    --modules;
    dii_module<BaseIterator> tmp = **this;
    typename dii_module<BaseIterator>::module_info_iterator
      info = gts::iterators::next<3>(tmp.begin ());
    if(info != tmp.end ())
      base_iterator = boost::end(*info);
    else
      base_iterator = last;
  }
  dii_module<BaseIterator> dereference () const
  {
    return dii_module<BaseIterator>(base_iterator, last);
  }

  BaseIterator base_iterator, last;
  unsigned int modules;
};

namespace download_info_indication_iterators {

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
struct download_id_iterator;

template <typename BaseIterator>
struct block_size_iterator;

template <typename BaseIterator>
struct window_size_iterator;

template <typename BaseIterator>
struct ack_period_iterator;

template <typename BaseIterator>
struct timeout_download_window_iterator;

template <typename BaseIterator>
struct timeout_download_scenario_iterator;

template <typename BaseIterator>
struct compatibility_descriptor_iterator;

template <typename BaseIterator>
struct module_range_iterator;

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 19
template <typename BaseIterator>
struct dii_module_range
{
  typedef dii_module_iterator<BaseIterator> iterator;
  typedef iterator const_iterator;
  typedef boost::mpl::size_t<0u> modules_bits_offset;
  typedef boost::mpl::size_t<16u> modules_bits_size;

  unsigned int modules () const
  {
    return algorithm::parse_data
      <unsigned int, modules_bits_offset::value, modules_bits_size::value>(first);
  }

  dii_module_range(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {
  }

  iterator begin () const
  {
    return iterator(boost::next(first, modules_bits_size::value/CHAR_BIT), last, modules());
  }
  iterator end () const
  {
    return iterator(last, last, 0);
  }

  BaseIterator first, last;
};

// Defined in ISO IEC 13818-6:1998 page 258
template <typename BaseIterator>
struct download_info_indication
{
  typedef download_info_indication_iterators::protocol_discriminator_iterator<BaseIterator>
    protocol_discriminator_iterator;
  typedef protocol_discriminator_iterator begin_iterator;
  typedef download_info_indication_iterators::dsmcc_type_iterator<BaseIterator>
    dsmcc_type_iterator;
  typedef download_info_indication_iterators::message_id_iterator<BaseIterator>
    message_id_iterator;
  typedef download_info_indication_iterators::transaction_id_iterator<BaseIterator>
    transaction_id_iterator;
  typedef download_info_indication_iterators::adaptation_iterator<BaseIterator>
    adaptation_iterator;
  typedef download_info_indication_iterators::download_id_iterator<BaseIterator>
    download_id_iterator;
  typedef download_info_indication_iterators::block_size_iterator<BaseIterator>
    block_size_iterator;
  typedef download_info_indication_iterators::window_size_iterator<BaseIterator>
    window_size_iterator;
  typedef download_info_indication_iterators::ack_period_iterator<BaseIterator>
    ack_period_iterator;
  typedef download_info_indication_iterators::timeout_download_window_iterator<BaseIterator>
    timeout_download_window_iterator;
  typedef download_info_indication_iterators::timeout_download_scenario_iterator<BaseIterator>
    timeout_download_scenario_iterator;
  typedef download_info_indication_iterators::compatibility_descriptor_iterator<BaseIterator>
    compatibility_descriptor_iterator;
  typedef download_info_indication_iterators::module_range_iterator<BaseIterator>
    module_range_iterator;
  typedef download_info_indication_iterators::private_data_iterator<BaseIterator>
    private_data_iterator;
  typedef download_info_indication_iterators::end_iterator<BaseIterator> end_iterator;

  typedef user_network_message<BaseIterator> base_type;

  download_info_indication(BaseIterator first, BaseIterator last)
    : base_message(first, last)
  {
  }
  download_info_indication(base_type base_message)
    : base_message(base_message)
  {
  }

  begin_iterator begin () const;
  end_iterator end () const;

  typedef BaseIterator base_iterator;
  base_iterator base_begin () const { return base_message.base_begin (); }
  base_iterator base_end () const { return base_message.base_end (); }
  
  base_type base_message;
};

namespace download_info_indication_iterators {

template <typename BaseIterator>
struct protocol_discriminator_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::protocol_discriminator_iterator
   , download_info_indication<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::protocol_discriminator_iterator
   , download_info_indication<BaseIterator>
   , dsmcc_type_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  protocol_discriminator_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct dsmcc_type_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::dsmcc_type_iterator
   , download_info_indication<BaseIterator>
   , message_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::dsmcc_type_iterator
   , download_info_indication<BaseIterator>
   , message_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  dsmcc_type_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct message_id_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::message_id_iterator
   , download_info_indication<BaseIterator>
   , transaction_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::message_id_iterator
   , download_info_indication<BaseIterator>
   , transaction_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  message_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct transaction_id_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::transaction_id_iterator
   , download_info_indication<BaseIterator>
   , adaptation_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::transaction_id_iterator
   , download_info_indication<BaseIterator>
   , adaptation_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  transaction_id_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct adaptation_iterator : gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::adaptation_iterator
   , download_info_indication<BaseIterator>
   , download_id_iterator<BaseIterator> >
{
  typedef gts::adaptation_iterator
  <typename user_network_message<BaseIterator>::adaptation_iterator
   , download_info_indication<BaseIterator>
   , download_id_iterator<BaseIterator> > adaptation_base;
  typedef typename adaptation_base::sequence_type sequence_type;
  typedef typename adaptation_base::adapted_iterator_type adapted_iterator_type;
  adaptation_iterator(sequence_type const& s, adapted_iterator_type i)
    : adaptation_base(s, i) {}
};

template <typename BaseIterator>
struct download_id_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<0u> payload_bits_offset;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef boost::uint_t<32u>::least deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  download_id_iterator(sequence_type const& sequence
                       , typename user_network_message<BaseIterator>::message_payload_iterator payload)
    : sequence(sequence)
    , payload_offset(payload.base ()) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef block_size_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct block_size_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<32u> payload_bits_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef unsigned int deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  block_size_iterator(sequence_type const& sequence
                      , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}

  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef window_size_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct window_size_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<48u> payload_bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  window_size_iterator(sequence_type const& sequence
                       , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef ack_period_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct ack_period_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<56u> payload_bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  ack_period_iterator(sequence_type const& sequence
                      , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef timeout_download_window_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct timeout_download_window_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<64u> payload_bits_offset;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef boost::uint_t<32u>::least deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  timeout_download_window_iterator(sequence_type const& sequence
                                   , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef timeout_download_scenario_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct timeout_download_scenario_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<96u> payload_bits_offset;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef boost::uint_t<32u>::least deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  timeout_download_scenario_iterator(sequence_type const& sequence
                                     , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, payload_bits_offset::value, bits_size::value>(payload_offset);
  }

  typedef compatibility_descriptor_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, payload_offset);
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct compatibility_descriptor_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<128u> payload_bits_offset;
  typedef descriptors::compatibility_descriptor<BaseIterator> deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  compatibility_descriptor_iterator(sequence_type const& sequence
                                    , BaseIterator payload_offset)
    : sequence(sequence), payload_offset(payload_offset) {}
  
  typedef BaseIterator base_type;
  base_type base () const
  { return algorithm::position<payload_bits_offset::value>(payload_offset); }

  deref_type operator*() const
  {
    deref_type tmp(base(), sequence.base_end());
    assert(*tmp.begin () <= std::distance(base (), sequence.base_end ()));
    return deref_type(base ()
                      , boost::next(base()
                                    , deref_type::descriptor_length_iterator
                                    ::bits_size::value/CHAR_BIT + *tmp.begin ()));
  }

  typedef module_range_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    deref_type tmp(base(), sequence.base_end ());
    return next_type(sequence
                     , boost::next(base ()
                                   , deref_type::descriptor_length_iterator
                                    ::bits_size::value/CHAR_BIT + *tmp.begin ()));
  }

  sequence_type const& sequence;
  BaseIterator payload_offset;
};

template <typename BaseIterator>
struct module_range_iterator
{
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef dii_module_range<BaseIterator> deref_type;
  typedef download_info_indication<BaseIterator> sequence_type;

  module_range_iterator(sequence_type const& sequence
                        , BaseIterator modules_offset)
    : sequence(sequence), modules_offset(modules_offset) {}

  typedef BaseIterator base_type;
  base_type base () const
  { return modules_offset; }

  deref_type operator*() const
  {
    return deref_type (modules_offset, sequence.base_end ());
  }

  typedef module_range_iterator<BaseIterator> next_type;
  next_type operator++() const;
  // {
  //   deref_type tmp(base(), sequence.base_end ());
  //   return next_type(sequence, boost::next(modules_offset, *tmp.begin ()));
  // }

  sequence_type const& sequence;
  BaseIterator modules_offset;
};

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename download_info_indication<BaseIterator>::begin_iterator
download_info_indication<BaseIterator>::begin () const
{
  return begin_iterator(*this, base_message.begin ());
}

template <typename BaseIterator>
typename dii_module<BaseIterator>::begin_iterator
dii_module<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename dii_module<BaseIterator>::end_iterator
dii_module<BaseIterator>::end () const
{
  return end_iterator(*this, last);
}

} }

#endif
