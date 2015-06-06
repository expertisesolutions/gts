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

#ifndef GTS_DSMCC_BIOP_BIOP_PROFILE_HPP
#define GTS_DSMCC_BIOP_BIOP_PROFILE_HPP

#include <gts/dsmcc/biop/object_location.hpp>
#include <gts/dsmcc/biop/conn_binder.hpp>

#include <boost/variant.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct biop_profile
{
  typedef boost::variant<biop::object_location<BaseIterator>
                         , biop::conn_binder> lite_component_variant;
  biop::object_location<BaseIterator> object_location;
  biop::conn_binder conn_binder;
  std::vector<lite_component_variant> lite_components;
};

template <typename BaseIterator>
bool operator==(biop_profile<BaseIterator> const& lhs, biop_profile<BaseIterator> const& rhs)
{
  return lhs.object_location == rhs.object_location
    && lhs.conn_binder == rhs.conn_binder;
}

template <typename BaseIterator>
bool operator<(biop_profile<BaseIterator> const& lhs, biop_profile<BaseIterator> const& rhs)
{
  return (lhs.object_location == rhs.object_location
          && lhs.conn_binder == rhs.conn_binder)
    || lhs.conn_binder < rhs.conn_binder;
}

} } }

#endif
