///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONSTANTS_ABNT_APPLICATION_CONTROL_CODE_HPP
#define GTS_CONSTANTS_ABNT_APPLICATION_CONTROL_CODE_HPP

namespace gts { namespace constants { namespace abnt {

namespace application_control_codes {

enum application_control_code
{
  autostart = 0x1
  , present = 0x2
  , destroy = 0x3
  , kill = 0x4
  , remote = 0x6
  , unbound = 0x7
};

}

} } }

#endif
