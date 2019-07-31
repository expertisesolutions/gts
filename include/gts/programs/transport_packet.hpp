///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAMS_PACKET_HPP
#define GTS_PROGRAMS_PACKET_HPP

namespace gts { namespace programs {

template <typename ESBuffer, typename Enable = void>
struct transport_packet
{
  typedef typename ESBuffer::transport_packet_type type;
};

} }

#endif
