///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAM_ES_BUFFER_CONCEPT_HPP
#define GTS_PROGRAM_ES_BUFFER_CONCEPT_HPP

#include <gts/programs/transport_packet.hpp>
#include <gts/programs/push_packet.hpp>
#include <gts/transport_packet_concept.hpp>

namespace gts { namespace programs {

template <typename X>
struct ESBufferConcept : boost::EqualityComparable<X>
  , boost::CopyConstructible<X>
{
  typedef typename programs::transport_packet<X>::type packet_type;

  BOOST_CONCEPT_ASSERT((TransportPacketConcept<packet_type>));

  BOOST_CONCEPT_USAGE(ESBufferConcept)
  {
    programs::push_packet(i, packet);
  }

  packet_type packet;
  X i;
};

} }

#endif
