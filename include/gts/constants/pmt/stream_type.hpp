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
