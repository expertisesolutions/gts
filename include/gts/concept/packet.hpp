///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONCEPT_PACKET_HPP
#define GTS_CONCEPT_PACKET_HPP

#include <gts/concept/convertible_to.hpp>

#include <boost/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

namespace gts { namespace concept {

template <typename T>
struct packet_traits
{
  typedef boost::mpl::false_ is_packet;
};

template <typename X>
struct Packet
{
  typedef packet_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_packet::value, ==, true);
  typedef typename traits::boolean_type boolean_type;
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::continuity_counter_type continuity_counter_type;
  typedef typename traits::adaptation_field_type adaptation_field_type;
  typedef typename traits::payload_type payload_type;

  BOOST_CONCEPT_USAGE(Packet)
  {
    convertible_to<boolean_type>(traits::transport_error_indicator(packet));
    convertible_to<boolean_type>(traits::payload_unit_start_indicator(packet));
    convertible_to<boolean_type>(traits::transport_priority(packet));
    convertible_to<identifier_type>(traits::identifier(packet));
    convertible_to<boolean_type>(traits::scramble_indicator(packet));
    convertible_to<boolean_type>(traits::adaptation_exists(packet));
    convertible_to<boolean_type>(traits::payload_exists(packet));
    convertible_to<continuity_counter_type>(traits::continuity_counter(packet));
    convertible_to<adaptation_field_type>(traits::adaptation_field(packet));
    convertible_to<payload_type>(traits::payload(packet));
  }

  X packet;
};

} }

#endif
