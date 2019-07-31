///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DESCRIPTORS_SERVICE_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_SERVICE_DESCRIPTOR_HPP

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

namespace service_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct service_type_iterator;

template <typename BaseIterator>
struct service_provider_name_length_iterator;

template <typename BaseIterator>
struct service_provider_name_iterator;

template <typename BaseIterator>
struct service_name_length_iterator;

template <typename BaseIterator>
struct service_name_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct service_descriptor : tagged_descriptor<BaseIterator>
{
  typedef service_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef service_descriptor_iterators::service_type_iterator<BaseIterator> service_type_iterator;
  typedef service_descriptor_iterators::service_provider_name_length_iterator<BaseIterator>
  service_provider_name_length_iterator;
  typedef service_descriptor_iterators::service_provider_name_iterator<BaseIterator>
  service_provider_name_iterator;
  typedef service_descriptor_iterators::service_name_length_iterator<BaseIterator> service_name_length_iterator;
  typedef service_descriptor_iterators::service_name_iterator<BaseIterator> service_name_iterator;
  typedef service_descriptor_iterators::end_iterator<BaseIterator> end_iterator;
  typedef tagged_descriptor<BaseIterator> base_type;

  begin_iterator begin() const;
  end_iterator end() const;

  service_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  service_descriptor(base_type base)
    : base_type(base) {}

  
};

namespace service_descriptor_iterators {

struct size_comparable {};
struct offset_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , service_descriptor<BaseIterator>
                        , typename service_descriptor<BaseIterator>::service_type_iterator
                        >
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef service_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , service_descriptor<BaseIterator>
                              , typename service_descriptor<BaseIterator>::service_type_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct service_type_iterator : static_offset_size_iterator
<service_type_iterator<BaseIterator>, BaseIterator
 , service_descriptor<BaseIterator>, boost::mpl::size_t<16u>
 , boost::mpl::size_t<8u>, unsigned int
 , service_provider_name_length_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef service_descriptor<BaseIterator> sequence_type;

  service_type_iterator(sequence_type const& sequence
                        , typename tagged_descriptor<BaseIterator>::data_iterator)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct service_provider_name_length_iterator : static_offset_size_iterator
<service_provider_name_length_iterator<BaseIterator>, BaseIterator
 , service_descriptor<BaseIterator>, boost::mpl::size_t<24u>
 , boost::mpl::size_t<8u>, unsigned int
 , service_provider_name_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef service_descriptor<BaseIterator> sequence_type;

  service_provider_name_length_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct service_name_internal
{
  service_name_internal(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef service_descriptor_iterators::service_name_length_iterator<BaseIterator>
  service_name_length_iterator;
  typedef service_name_length_iterator begin_iterator;
  typedef service_descriptor_iterators::service_name_iterator<BaseIterator>
  service_name_iterator;

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;

  BaseIterator first, last;
};

template <typename BaseIterator>
struct service_provider_name_iterator
{
  typedef BaseIterator base_type;
  typedef service_descriptor<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef service_name_length_iterator<BaseIterator> next_type;
  typedef iterators::forward_iterator_tag iterator_tag;

  service_provider_name_iterator(sequence_type const& sequence)
  : sequence(sequence), size_(0)
  {
    size_ = *gts::iterators::next<2>(sequence.begin());
    size_ = (std::min<unsigned int>)
      (size_, std::distance(base(), sequence.base_end()));
  }
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); }
  unsigned int size() const
  {
    return size_;
  }
  deref_type operator*() const
  {
    return deref_type(base(), boost::next(base(), size()));
  }
  next_type operator++() const
  {
    return next_type(service_name_internal<BaseIterator>
                     (boost::next(base(), size_)
                      , sequence.base_end()));
  }  
  
  sequence_type sequence;
  unsigned int size_;
};

template <typename BaseIterator>
struct service_name_length_iterator : static_offset_size_iterator
<service_name_length_iterator<BaseIterator>, BaseIterator
 , service_name_internal<BaseIterator>, boost::mpl::size_t<0u>
 , boost::mpl::size_t<8u>, unsigned int
 , service_name_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef service_name_internal<BaseIterator> sequence_type;

  service_name_length_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct service_name_iterator
{
  typedef BaseIterator base_type;
  typedef service_name_internal<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef iterators::forward_iterator_tag iterator_tag;

  service_name_iterator(sequence_type const& sequence)
  : sequence(sequence), size_(0)
  {
    size_ = *sequence.begin();
    size_ = (std::min<unsigned int>)
      (size_, std::distance(base(), sequence.base_end()));
  }
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); }
  unsigned int size() const
  {
    return size_;
  }
  deref_type operator*() const
  {
    return deref_type(base(), boost::next(base(), size()));
  }
  next_type operator++() const
  {
    return next_type(sequence);
  }  
  
  sequence_type sequence;
  unsigned int size_;
};

template <typename BaseIterator>
struct end_iterator;

template <typename BaseIterator>
typename service_name_internal<BaseIterator>::begin_iterator service_name_internal<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

}

template <typename BaseIterator>
typename service_descriptor<BaseIterator>::begin_iterator service_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}
template <typename BaseIterator>
typename service_descriptor<BaseIterator>::end_iterator service_descriptor<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} }

#endif
