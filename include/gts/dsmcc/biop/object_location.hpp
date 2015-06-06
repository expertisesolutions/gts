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

#ifndef GTS_DSMCC_BIOP_OBJECT_LOCATION_HPP
#define GTS_DSMCC_BIOP_OBJECT_LOCATION_HPP

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct object_location
{
  object_location()
    : carousel_id(0u), module_id(0u) {}

  unsigned int carousel_id;
  unsigned int module_id;
  boost::iterator_range<BaseIterator> object_key;
};

template <typename BaseIterator>
bool operator==(object_location<BaseIterator> const& lhs, object_location<BaseIterator>const& rhs)
{
  return lhs.carousel_id == rhs.carousel_id && lhs.module_id == rhs.module_id
    && lhs.object_key == rhs.object_key;
}

template <typename BaseIterator>
bool operator<(object_location<BaseIterator> const& lhs, object_location<BaseIterator>const& rhs)
{
  return (lhs.carousel_id == rhs.carousel_id && lhs.module_id == rhs.module_id
          && lhs.object_key < rhs.object_key)
    || (lhs.carousel_id == rhs.carousel_id && lhs.module_id < rhs.module_id)
    || lhs.carousel_id < rhs.carousel_id;
}

} } }

#endif
