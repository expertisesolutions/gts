///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DESCRIPTORS_TAGGED_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_TAGGED_DESCRIPTOR_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/static_offset_size_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace descriptors {

namespace tagged_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct tagged_descriptor
{
  typedef tagged_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef tagged_descriptor_iterators::data_iterator<BaseIterator> data_iterator;
  typedef tagged_descriptor_iterators::end_iterator<BaseIterator> end_iterator;

  tagged_descriptor(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

namespace tagged_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator : static_offset_size_iterator
  <tag_iterator<BaseIterator>, BaseIterator, tagged_descriptor<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<8u>, unsigned int
   , data_iterator<BaseIterator> >
{
  typedef tagged_descriptor<BaseIterator> sequence_type;

  tag_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct data_iterator
{
  typedef boost::mpl::size_t<16u> bits_offset;
  typedef tagged_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;

  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  data_iterator(sequence_type const& sequence)
  : sequence(sequence) {}

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); }
  deref_type operator*() const
  {
    typedef boost::mpl::size_t<8u> size_bits_offset;
    typedef boost::mpl::size_t<8u> size_bits_size;
    unsigned int size = algorithm::parse_data
      <unsigned int
       , size_bits_offset::value, size_bits_size::value>
      (sequence.base_begin());
    unsigned int new_size = (std::min<unsigned int>)
      (size, std::distance(base(), sequence.base_end()));
    return deref_type(base(), boost::next(base(), new_size));
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const { return next_type(sequence); }
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename tagged_descriptor<BaseIterator>::begin_iterator tagged_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename tagged_descriptor<BaseIterator>::end_iterator tagged_descriptor<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} }

#endif
