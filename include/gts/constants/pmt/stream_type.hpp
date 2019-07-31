///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONSTANTS_PMT_STREAM_TYPE_HPP
#define GTS_CONSTANTS_PMT_STREAM_TYPE_HPP

namespace gts { namespace constants { namespace pmt {

namespace stream_types {

enum stream_type
{
  video = 0x1
  , mpeg4_video = 0x2
  , audio = 0x3
  , aac_audio = 0x4
  , private_sections = 0x5
  , pes_private_data = 0x6
  , mheg = 0x7
  , dsmcc_unspecified = 0x8
  , dsmcc_type_a = 0xa
  , dsmcc_type_b = 0xb
  , dsmcc_type_c = 0xc
  , dsmcc_type_d = 0xd
};

}

using stream_types::stream_type;

} } }

#endif
