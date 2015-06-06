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

#ifndef GTS_ITERATORS_ALGORITHM_FOR_EACH_HPP
#define GTS_ITERATORS_ALGORITHM_FOR_EACH_HPP

#include <gts/iterators/next.hpp>

namespace gts { namespace iterators { namespace algorithm {

namespace for_each_detail {

template <typename First, typename Last, typename F>
inline void for_each(First const&, Last const&, F const&, boost::mpl::true_)
{
}

template <typename First, typename Last, typename F>
inline void for_each(First first, Last last, F f, boost::mpl::false_)
{
  if(first != last)
  {
    f(*first);
    for_each_detail::for_each(++first, last, f
                              , typename boost::is_same
                              <typename iterators::result_of::next<First>::type
                               , Last>::type());
  }
}

}

template <typename First, typename Last, typename F>
void for_each(First first, Last last, F f)
{
  return for_each_detail::for_each(first, last, f
                                   , typename boost::is_same<First, Last>::type());
}

} } }

#endif
