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
