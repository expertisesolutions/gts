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

#ifndef GTS_ITERATORS_DEREF_HPP
#define GTS_ITERATORS_DEREF_HPP

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct deref
{
  typedef typename Iterator::deref_type type;
};

}

template <typename Iterator, typename Enable = void>
struct deref_impl
{
  static typename iterators::result_of::deref<Iterator>::type
  run(Iterator const& iterator)
  {
    return *iterator;
  }
};

template <typename Iterator>
typename iterators::result_of::deref<Iterator>::type deref(Iterator const& iterator)
{
  return iterators::deref_impl<Iterator>::run(iterator);
}

} }

#endif
