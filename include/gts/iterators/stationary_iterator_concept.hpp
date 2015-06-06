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

#ifndef GTS_ITERATORS_END_ITERATOR_CONCEPT_HPP
#define GTS_ITERATORS_END_ITERATOR_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/iterators/iterator_tag.hpp>
#include <gts/iterators/base.hpp>

namespace gts { namespace iterators {

template <typename X>
struct StationaryIteratorConcept : boost::EqualityComparable<X>
  , boost::CopyConstructible<X>
{
  typedef typename iterators::iterator_tag<X>::type iterator_tag;
  typedef typename iterators::result_of::base<X>::type base_type;
  BOOST_MPL_ASSERT((boost::is_convertible<iterator_tag, stationary_iterator_tag>));
};

} }

#endif
