/* (c) Copyright 2011-2014 Felipe Magno de Almeida
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
