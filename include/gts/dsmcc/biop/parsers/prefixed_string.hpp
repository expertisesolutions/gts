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

#ifndef GTS_DSMCC_BIOP_PARSERS_PREFIXED_STRING_HPP
#define GTS_DSMCC_BIOP_PARSERS_PREFIXED_STRING_HPP

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <std::size_t SizeBits, typename BaseIterator>
boost::iterator_range<BaseIterator> prefixed_string(BaseIterator& first, BaseIterator last)
{
  std::size_t max_size = std::distance(first, last);
  if(max_size >= SizeBits/CHAR_BIT)
  {
    typename boost::uint_t<SizeBits>::least size = algorithm::parse_data
      <typename boost::uint_t<SizeBits>::least, 0u, SizeBits>(first);
    first = algorithm::position<SizeBits>(first);
    size = (std::min<std::size_t>)(max_size, size);
    BaseIterator last_string = boost::next(first, size);
    boost::iterator_range<BaseIterator> string(first, last_string);
    first = last_string;
    return string;
  }
  else
  {
    first = last;
    boost::iterator_range<BaseIterator> string(last, last);
    return string;
  }
}

} } } }

#endif
