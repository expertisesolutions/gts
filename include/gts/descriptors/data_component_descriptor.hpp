///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

// Defined in ARIB STD - B10 4.6 - E2 page 124
#ifndef GTS_DESCRIPTORS_DATA_COMPONENT_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_DATA_COMPONENT_DESCRIPTOR_HPP

#include <gts/descriptors/tagged_descriptor.hpp>
#include <gts/adaptation_iterator.hpp>

namespace gts { namespace descriptors {

namespace data_component_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct data_component_id_iterator;

template <typename BaseIterator>
struct additional_data_component_info_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ARIB STD - B10 4.6 - E2 page 124
template <typename BaseIterator>
struct data_component_descriptor : tagged_descriptor<BaseIterator>
{
  typedef data_component_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef data_component_descriptor_iterators::data_component_id_iterator<BaseIterator> data_component_id_iterator;
  typedef data_component_descriptor_iterators::additional_data_component_info_iterator<BaseIterator>
    additional_data_component_info_iterator;
  typedef data_component_descriptor_iterators::end_iterator<BaseIterator> end_iterator;
  typedef tagged_descriptor<BaseIterator> base_type;

  begin_iterator begin() const;
  end_iterator end() const;

  data_component_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  data_component_descriptor(base_type base)
    : base_type(base) {}
};

namespace data_component_descriptor_iterators {

struct size_comparable {};
struct offset_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , data_component_descriptor<BaseIterator>
                        , typename data_component_descriptor<BaseIterator>
                          ::data_component_id_iterator
                        >
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef data_component_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , data_component_descriptor<BaseIterator>
                              , typename data_component_descriptor<BaseIterator>
                                ::data_component_id_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct data_component_id_iterator : static_offset_size_iterator
  <data_component_id_iterator<BaseIterator>, BaseIterator
   , tagged_descriptor<BaseIterator>
   , boost::mpl::size_t<16u>, boost::mpl::size_t<16u>, unsigned int
   , additional_data_component_info_iterator<BaseIterator> >
{
  typedef tagged_descriptor<BaseIterator> sequence_type;

  data_component_id_iterator(sequence_type const& sequence
                             , typename sequence_type::data_iterator)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct additional_data_component_info_iterator;

}

template <typename BaseIterator>
typename data_component_descriptor<BaseIterator>::begin_iterator
data_component_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} }

#endif

