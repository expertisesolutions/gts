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

#ifndef GTS_DSMCC_BIOP_PARSERS_SERVICE_CONTEXT_LIST_HPP
#define GTS_DSMCC_BIOP_PARSERS_SERVICE_CONTEXT_LIST_HPP

#include <boost/range/iterator_range.hpp>

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <typename BaseIterator>
boost::iterator_range<BaseIterator> service_context_list(BaseIterator& first, BaseIterator last)
{
  typedef boost::mpl::int_<8u> size_bits_size;
  if(std::distance(first, last) < size_bits_size::value/CHAR_BIT)
    return boost::iterator_range<BaseIterator>(first, first);
  else
  {
    boost::uint_t<16u>::least size = algorithm::parse_data
      <boost::uint_t<16u>::least, 0u, size_bits_size::value>(first);
    first = algorithm::position<size_bits_size::value>(first);
    BaseIterator range_first = first;
    std::advance(first, (std::min<int>)(std::distance(first, last), size));
    return boost::make_iterator_range(range_first, first);
  }
}

} } } }

#endif

