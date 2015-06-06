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

#ifndef GTS_CONCEPT_RANDOM_ACCESS_SEQUENCE_HPP
#define GTS_CONCEPT_RANDOM_ACCESS_SEQUENCE_HPP

#include <gts/concept/convertible_to.hpp>
#include <gts/begin.hpp>
#include <gts/end.hpp>

#include <boost/concept_check.hpp>

namespace gts { namespace concept {

template <typename X>
struct RandomAccessSequence
{
  typedef gts::result_of::begin<X>::type begin_iterator;
  typedef gts::result_of::end<X>::type end_iterator;

  BOOST_CONCEPT_USAGE(RandomAccessSequence)
  {
    convertible_to<begin_iterator>(gts::begin(i));
    convertible_to<end_iterator>(gts::end(i));
  }

  X i;
};

} }

#endif
