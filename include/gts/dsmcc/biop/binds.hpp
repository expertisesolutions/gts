///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

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
