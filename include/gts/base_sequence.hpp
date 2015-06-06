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

#ifndef GTS_BASE_SEQUENCE_HPP
#define GTS_BASE_SEQUENCE_HPP

namespace gts {

template <typename BaseIterator>
struct base_sequence
{
  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  base_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  BaseIterator first, last;
};

}

#endif
