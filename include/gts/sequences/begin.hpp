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

#ifndef GTS_SEQUENCES_BEGIN_HPP
#define GTS_SEQUENCES_BEGIN_HPP

namespace gts { namespace sequences { namespace result_of {

template <typename Sequence, typename Enable = void>
struct begin
{
  typedef typename Sequence::begin_iterator type;
};

}

template <typename Sequence, typename Enable = void>
struct begin_impl
{
  static typename sequences::result_of::begin<Sequence>::type
  run(Sequence const& s)
  {
    return s.begin();
  }
};

template <typename Sequence>
typename sequences::result_of::begin<Sequence>::type begin(Sequence const& s)
{
  return sequences::begin_impl<Sequence>::run(s);
}

} }

#endif
