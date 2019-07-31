///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_TRANSPORT_PACKET_CONCEPT_HPP
#define GTS_TRANSPORT_PACKET_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/concept/convertible_to.hpp>
#include <gts/sequences/sequence_concept.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>

namespace gts {

template <typename X>
struct TransportPacketConcept : boost::CopyConstructible<X>
  , boost::EqualityComparable<X>, gts::sequences::SequenceConcept<X>
{
  typedef typename X::sync_byte_iterator sync_byte_iterator;
  typedef typename X::transport_error_indicator_iterator transport_error_indicator_iterator;
  typedef typename X::payload_unit_start_indicator_iterator payload_unit_start_indicator_iterator;
  typedef typename X::transport_priority_iterator transport_priority_iterator;
  typedef typename X::pid_iterator pid_iterator;
  typedef typename X::transport_scrambling_control_iterator transport_scrambling_control_iterator;
  typedef typename X::adaptation_field_control_iterator adaptation_field_control_iterator;
  typedef typename X::continuity_counter_iterator continuity_counter_iterator;
  typedef typename X::adaptation_field_iterator adaptation_field_iterator;
  typedef typename X::payload_iterator payload_iterator;
  typedef typename X::end_iterator end_iterator;

  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<sync_byte_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<transport_error_indicator_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<payload_unit_start_indicator_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<transport_priority_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<pid_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<transport_scrambling_control_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<adaptation_field_control_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<continuity_counter_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<adaptation_field_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<payload_iterator>));
  BOOST_CONCEPT_ASSERT((iterators::StationaryIteratorConcept<end_iterator>));

  BOOST_CONCEPT_USAGE(TransportPacketConcept)
  {
    concept::convertible_to<sync_byte_iterator>(sequences::begin(packet));
    concept::convertible_to<end_iterator>(sequences::end(packet));
    concept::convertible_to<transport_error_indicator_iterator>(iterators::next(sync_byte));
    concept::convertible_to<payload_unit_start_indicator_iterator>(iterators::next(transport_error_indicator));
    concept::convertible_to<transport_priority_iterator>(iterators::next(payload_unit_start_indicator));
    concept::convertible_to<pid_iterator>(iterators::next(transport_priority));
    concept::convertible_to<transport_scrambling_control_iterator>(iterators::next(pid));
    concept::convertible_to<adaptation_field_control_iterator>(iterators::next(transport_scrambling_control));
    concept::convertible_to<continuity_counter_iterator>(iterators::next(adaptation_field_control));
    concept::convertible_to<adaptation_field_iterator>(iterators::next(continuity_counter));
    concept::convertible_to<payload_iterator>(iterators::next(adaptation_field));
    concept::convertible_to<end_iterator>(iterators::next(payload));
  }

  X packet;
  sync_byte_iterator sync_byte;
  transport_error_indicator_iterator transport_error_indicator;
  payload_unit_start_indicator_iterator payload_unit_start_indicator;
  transport_priority_iterator transport_priority;
  pid_iterator pid;
  transport_scrambling_control_iterator transport_scrambling_control;
  adaptation_field_control_iterator adaptation_field_control;
  continuity_counter_iterator continuity_counter;
  adaptation_field_iterator adaptation_field;
  payload_iterator payload;
  end_iterator end;
};

}

#endif
