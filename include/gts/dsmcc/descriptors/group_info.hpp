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

#ifndef GTS_DSMCC_DESCRIPTORS_GROUP_INFO_HPP
#define GTS_DSMCC_DESCRIPTORS_GROUP_INFO_HPP

#include <gts/dsmcc/descriptors/compatibility_descriptor.hpp>

#include <boost/integer.hpp>

namespace gts { namespace dsmcc { namespace descriptors {

template <typename BaseIterator>
struct group_info
{
  boost::uint_t<32u>::least group_id, group_size;
  compatibility_descriptor<BaseIterator> group_compatibility;
  boost::iterator_range<BaseIterator> group_info;
  boost::iterator_range<BaseIterator> private_data;
};

} } }

#endif
