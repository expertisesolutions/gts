///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DESCRIPTOR_PRIVATE_RANGE_HPP
#define GTS_DESCRIPTOR_PRIVATE_RANGE_HPP

#include <gts/descriptors/tagged_descriptor.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts {

template <typename BaseIterator>
struct descriptor_private_range
{
  descriptor_private_range(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {
  }

  struct iterator : boost::iterator_facade<iterator
                                           , descriptors::tagged_descriptor<BaseIterator>
                                           , boost::forward_traversal_tag
                                           , descriptors::tagged_descriptor<BaseIterator> >
  {
    iterator(BaseIterator item_first, BaseIterator last)
      : item_first(item_first), last(last)
    {
      set_item_last ();
    }

    void set_item_last ()
    {
      typedef descriptors::tagged_descriptor<BaseIterator> descriptor_type;
      typedef typename descriptor_type::data_iterator data_iterator;
      descriptor_type deref (item_first, last);
      unsigned int length = boost::distance(*gts::iterators::next(deref.begin ()));
      item_last = last;
      if(std::distance(item_first, last) > length)
        item_last = boost::next(item_first, length + data_iterator::bits_offset::value / CHAR_BIT);
    }

    void increment ()
    {
      item_first = item_last;
      set_item_last ();
    }
    bool equal(iterator const& other) const
    {
      return item_first == other.item_first;
    }
    descriptors::tagged_descriptor<BaseIterator> dereference () const
    {
      return descriptors::tagged_descriptor<BaseIterator>(item_first, item_last);
    }

    BaseIterator item_first, item_last, last;
  };
  typedef iterator const_iterator;

  iterator begin () const
  {
    return iterator(first, last);
  }
  iterator end () const
  {
    return iterator(last, last);
  }

  BaseIterator first, last;
};

}

#endif
