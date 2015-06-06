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

#ifndef GTS_DSMCC_BIOP_IOP_IOR_HPP
#define GTS_DSMCC_BIOP_IOP_IOR_HPP

#include <gts/dsmcc/biop/biop_profile.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct iop_ior
{
  iop_ior() {}
  iop_ior(boost::iterator_range<BaseIterator> type_id)
    : type_id(type_id) {}
  
  boost::iterator_range<BaseIterator> type_id;
  std::vector<biop_profile<BaseIterator> > biop_profiles;
};

template <typename BaseIterator>
bool operator==(iop_ior<BaseIterator> const& lhs, iop_ior<BaseIterator> const& rhs)
{
  return lhs.type_id == rhs.type_id && lhs.biop_profiles == rhs.biop_profiles;
}

template <typename BaseIterator>
bool operator<(iop_ior<BaseIterator> const& lhs, iop_ior<BaseIterator> const& rhs)
{
  return (lhs.type_id == rhs.type_id && lhs.biop_profiles < rhs.biop_profiles)
    || lhs.type_id < rhs.type_id;
}

} } }

#endif
