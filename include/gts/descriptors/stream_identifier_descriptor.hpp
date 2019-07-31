///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DESCRIPTORS_STREAM_IDENTIFIER_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_STREAM_IDENTIFIER_DESCRIPTOR_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/descriptors/tagged_descriptor.hpp>
#include <gts/static_offset_size_iterator.hpp>
#include <gts/adaptation_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace descriptors {

namespace stream_identifier_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct component_tag_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ETSI 300 468 v1.6.1 (2004-11) page 63
template <typename BaseIterator>
struct stream_identifier_descriptor : tagged_descriptor<BaseIterator>
{
  typedef tagged_descriptor<BaseIterator> base_type;
  typedef stream_identifier_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef stream_identifier_descriptor_iterators::component_tag_iterator<BaseIterator>
    component_tag_iterator;
  typedef stream_identifier_descriptor_iterators::end_iterator<BaseIterator> end_iterator;
  
  begin_iterator begin() const;
  end_iterator end() const;

  stream_identifier_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  stream_identifier_descriptor(base_type base)
    : base_type(base) {}
};

namespace stream_identifier_descriptor_iterators {

struct size_comparable {};
struct offset_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , stream_identifier_descriptor<BaseIterator>
                        , typename stream_identifier_descriptor<BaseIterator>
                          ::component_tag_iterator
                        >
  , offset_comparable, size_comparable
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef stream_identifier_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , stream_identifier_descriptor<BaseIterator>
                              , typename stream_identifier_descriptor<BaseIterator>
                                ::component_tag_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct component_tag_iterator : static_offset_size_iterator
<component_tag_iterator<BaseIterator>, BaseIterator
 , stream_identifier_descriptor<BaseIterator>, boost::mpl::size_t<16u>
 , boost::mpl::size_t<8u>, unsigned int
 , end_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef stream_identifier_descriptor<BaseIterator> sequence_type;

  component_tag_iterator
  (sequence_type const& sequence
   , typename tagged_descriptor<BaseIterator>::data_iterator)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename stream_identifier_descriptor<BaseIterator>::begin_iterator
stream_identifier_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} }

#endif
