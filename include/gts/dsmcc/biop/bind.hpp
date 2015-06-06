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

#ifndef GTS_DSMCC_BIOP_BIND_HPP
#define GTS_DSMCC_BIOP_BIND_HPP

#include <gts/dsmcc/biop/iop_ior.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct bind_name
{
  bind_name(boost::iterator_range<BaseIterator> id
            , boost::iterator_range<BaseIterator> kind)
    : id(id), kind(kind)
  {
  }
  
  boost::iterator_range<BaseIterator> id, kind;
};

template <typename BaseIterator>
struct bind
{
  typedef biop::bind_name<BaseIterator> bind_name;
  bind(std::vector<bind_name> names)
    : names(names)
    , binding_type(1u) {}
  bind()
    : binding_type(1u) {}

  std::vector<bind_name> names;
  boost::uint_t<8>::least binding_type;
  biop::iop_ior<BaseIterator> ior;
};

} } }

#endif
