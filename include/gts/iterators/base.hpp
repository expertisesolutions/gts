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

#ifndef GTS_ITERATORS_BASE_HPP
#define GTS_ITERATORS_BASE_HPP

namespace gts { namespace iterators { namespace result_of {

template <typename Iterator, typename Enable = void>
struct base
{
  typedef typename Iterator::base_type type;
};

}

template <typename Iterator, typename Enable = void>
struct base_impl
{
  static typename iterators::result_of::base<Iterator>::type
  run(Iterator const& iterator)
  {
    return iterator.base();
  }
};

template <typename Iterator>
typename result_of::base<Iterator>::type base(Iterator const& iterator)
{
  return base_impl<Iterator>::run(iterator);
}

} }

#endif
