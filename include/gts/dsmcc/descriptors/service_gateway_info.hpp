///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DESCRIPTORS_SERVICE_GATEWAY_INFO_HPP
#define GTS_DSMCC_DESCRIPTORS_SERVICE_GATEWAY_INFO_HPP

#include <gts/dsmcc/biop/iop_ior.hpp>
#include <gts/dsmcc/biop/parsers/iop_ior.hpp>

namespace gts { namespace dsmcc { namespace descriptors {

namespace service_gateway_info_iterators {

template <typename BaseIterator>
struct object_ref_iterator;

template <typename BaseIterator>
struct taps_iterator;

template <typename BaseIterator>
struct service_context_list_iterator;

template <typename BaseIterator>
struct user_info_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct service_gateway_info
{
  typedef service_gateway_info_iterators::object_ref_iterator<BaseIterator>
    object_ref_iterator;
  typedef object_ref_iterator begin_iterator;
  typedef service_gateway_info_iterators::taps_iterator<BaseIterator> taps_iterator;
  typedef service_gateway_info_iterators::service_context_list_iterator<BaseIterator>
    service_context_list_iterator;
  typedef service_gateway_info_iterators::user_info_iterator<BaseIterator>
    user_info_iterator;
  typedef service_gateway_info_iterators::end_iterator<BaseIterator> end_iterator;

  service_gateway_info(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  begin_iterator begin() const;
  end_iterator end() const;

  typedef BaseIterator base_iterator;
  
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  base_iterator first, last;
};

namespace service_gateway_info_iterators {

template <typename BaseIterator>
struct object_ref_iterator
{
  typedef service_gateway_info<BaseIterator> sequence_type;
  typedef biop::iop_ior<BaseIterator> deref_type;
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  typedef taps_iterator<BaseIterator> next_type;

  object_ref_iterator(sequence_type const& sequence)
  : sequence(sequence), next_it(sequence.base_begin())
  {
    object_ref = dsmcc::biop::parsers::iop_ior(next_it, sequence.base_end());
  }

  base_type base() const { return sequence.base_begin(); }
  deref_type operator*() const { return object_ref; }
  next_type operator++() const { return next_type(sequence); }

  sequence_type sequence;
  deref_type object_ref;
  BaseIterator next_it;
};

template <typename BaseIterator>
struct taps_iterator;

template <typename BaseIterator>
struct service_context_list_iterator;

template <typename BaseIterator>
struct user_info_iterator;

}

template <typename BaseIterator>
typename service_gateway_info<BaseIterator>::begin_iterator
service_gateway_info<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} } }

#endif
