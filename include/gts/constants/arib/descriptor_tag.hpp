///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONSTANTS_ARIB_DESCRIPTOR_HPP
#define GTS_CONSTANTS_ARIB_DESCRIPTOR_HPP

namespace gts { namespace constants { namespace arib {

namespace descriptor_tags {

enum descriptor_tag
{
  data_component_descriptor = 0xfd
  , application_descriptor = 0x00
  , application_name_descriptor = 0x01
  , application_icons_descriptor = 0xb
  , external_application_authorisation_descriptor = 0x05
  , graphics_constraints_descriptor = 0x14
  , transport_protocol_descriptor = 0x02
  , simple_application_location_descriptor = 0x15
  , simple_application_boundary_descriptor = 0x17
  //, data_broadcast_descriptor = 
  , ginga_j_application_descriptor = 0x03
  , ginga_j_application_location_descriptor = 0x04
  , ginga_ncl_application_location_descriptor = 0x07
};

}

} } }

#endif
