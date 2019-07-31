///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_STREAMBUF_PACKET_HPP
#define GTS_STREAMBUF_PACKET_HPP

#include <gts/concept/packet.hpp>

#include <boost/integer.hpp>
#include <iosfwd>
#include <cassert>

namespace gts {

struct streambuf_packet
{
  streambuf_packet(std::streambuf& streambuf)
    : streambuf(&streambuf)
    , bytes_read(3)
  {
    unsigned char c = streambuf.sbumpc();
    transport_error_indicator = 0x80 & c;
    payload_unit_start_indicator = 0x40 & c;
    transport_priority_indicator = 0x20 & c;
    unsigned char pid_least = streambuf.sbumpc();
    pid = ((0x1F & c) << 8) + pid_least;
    unsigned char flags_and_counter = streambuf.sbumpc();
    assert((flags_and_counter & 0xC0) == 0);
    adaptation_exists = flags_and_counter & 0x20;
    payload_exists = flags_and_counter & 0x10;
    continuity_counter = 0xF & flags_and_counter;
  }

  std::streambuf* streambuf;
  std::size_t bytes_read;
  bool transport_error_indicator
    , payload_unit_start_indicator
    , transport_priority_indicator
    , adaptation_exists
    , payload_exists;
  boost::uint_t<16>::least pid;
  boost::uint_t<8>::least continuity_counter;
};

}

#endif
