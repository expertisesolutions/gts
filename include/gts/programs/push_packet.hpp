///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAMS_PUSH_PACKET_HPP
#define GTS_PROGRAMS_PUSH_PACKET_HPP

namespace gts { namespace programs {

template <typename ESBuffer, typename Enable = void>
struct push_packet_impl
{
  template <typename Packet>
  static void run(ESBuffer& buffer, Packet const& packet)
  {
    buffer.push_packet(packet);
  }
};

template <typename ESBuffer, typename Packet>
void push_packet(ESBuffer& buffer, Packet const& packet)
{
  push_packet_impl<ESBuffer>::run(buffer, packet);
}

} }

#endif
