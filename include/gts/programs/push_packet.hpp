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

#ifndef GTS_PROGRAMS_PUSH_PACKET_HPP
#define GTS_PROGRAMS_PUSH_PACKET_HPP

namespace gts { namespace programs {

template <typename ESBuffer, typename Enable = void>
struct push_packet_impl
{
  template <typename Packet>
  static void run(ESBuffer& buffer, Packet const& packet)
  {
    buffer.push_packet(packet);
  }
};

template <typename ESBuffer, typename Packet>
void push_packet(ESBuffer& buffer, Packet const& packet)
{
  push_packet_impl<ESBuffer>::run(buffer, packet);
}

} }

#endif
