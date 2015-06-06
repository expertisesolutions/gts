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

#ifndef GTS_DSMCC_BIOP_BINDS_HPP
#define GTS_DSMCC_BIOP_BINDS_HPP

#include <gts/dsmcc/biop/bind.hpp>
#include <gts/dsmcc/biop/parsers/bind.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct binds
{
  binds(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  struct iterator : boost::iterator_facade
  <iterator, bind<BaseIterator>, boost::forward_traversal_tag
   , bind<BaseIterator> >
  {
    iterator(unsigned int current_index, unsigned int last_index
             , BaseIterator first_it, BaseIterator last_it)
      : current_it(first_it), last_it(last_it)
      , current_index(current_index), last_index(last_index)
      , bind(parsers::bind(first_it, last_it))
      , next_it(first_it)
    {
    }

    bool equal (iterator const& other) const
    {
      return other.current_index == current_index
        || current_it == other.current_it;
    }
    void increment ()
    {
      ++current_index;
      current_it = next_it;
      bind = parsers::bind(next_it, last_it);
    }
    biop::bind<BaseIterator> dereference() const { return bind; }
    BaseIterator base() const { return current_it; }

    BaseIterator current_it, last_it;
    unsigned int current_index, last_index;
    biop::bind<BaseIterator> bind;
    BaseIterator next_it;
  };
  typedef iterator const_iterator;

  iterator begin() const
  {
    unsigned int max = algorithm::parse_data
      <boost::uint_t<16u>::least, 0u, 16u>(first);
    return iterator(0u, max, algorithm::position<16u>(first), last);
  }
  iterator end() const
  {
    unsigned int max = algorithm::parse_data
      <boost::uint_t<16u>::least, 0u, 16u>(first);
    return iterator(max, max, last, last);
  }

  BaseIterator first, last;
};

} } }

#endif
