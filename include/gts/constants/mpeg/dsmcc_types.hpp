///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONSTANTS_MPEG_DSMCC_TYPES_HPP
#define GTS_CONSTANTS_MPEG_DSMCC_TYPES_HPP

namespace gts { namespace constants { namespace mpeg {

namespace dsmcc_types {

enum dsmcc_type
{
  llcsnap = 0x3a
  , user_network = 0x3b
  , download = 0x3c
  , descriptors = 0x3d
  , private_data = 0x3e
};

}

} } }

#endif
