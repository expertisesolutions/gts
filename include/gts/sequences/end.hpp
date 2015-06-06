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

#ifndef GTS_SEQUENCES_END_HPP
#define GTS_SEQUENCES_END_HPP

namespace gts { namespace sequences { namespace result_of {

template <typename Sequence, typename Enable = void>
struct end
{
  typedef typename Sequence::end_iterator type;
};

}

template <typename Sequence, typename Enable = void>
struct end_impl
{
  static typename sequences::result_of::end<Sequence>::type
  run(Sequence const& s)
  {
    return s.end();
  }
};

template <typename Sequence>
typename sequences::result_of::end<Sequence>::type end(Sequence const& s)
{
  return sequences::end_impl<Sequence>::run(s);
}

} }

#endif
