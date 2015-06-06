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
