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

#ifndef GTS_DSMCC_BIOP_FILE_OBJECT_INFO_HPP
#define GTS_DSMCC_BIOP_FILE_OBJECT_INFO_HPP

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct file_object_info
{
  typedef boost::uint_t<64>::least content_size_type;
  file_object_info(content_size_type content_size
                   , boost::iterator_range<BaseIterator> rest)
    : content_size_(content_size), rest_(rest) {}

  content_size_type content_size() const { return content_size_; }
  boost::iterator_range<BaseIterator> rest() const { return rest_; }

  content_size_type content_size_;
  boost::iterator_range<BaseIterator> rest_;
};

} } }

#endif
