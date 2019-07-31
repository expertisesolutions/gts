///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DESCRIPTORS_APPLICATION_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_APPLICATION_DESCRIPTOR_HPP

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

namespace application_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct application_profiles_length_iterator;

template <typename BaseIterator>
struct application_profiles_iterator;

template <typename BaseIterator>
struct service_bound_flag_iterator;

template <typename BaseIterator>
struct visibility_iterator;

template <typename BaseIterator>
struct application_priority_iterator;

template <typename BaseIterator>
struct transport_protocol_label_iterator;

template <typename BaseIterator>
struct end_iterator;

}

namespace application_descriptor_detail {

template <typename BaseIterator>
struct application_profile
{
  typedef boost::mpl::size_t<40u> bits_size;
};

template <typename BaseIterator>
struct application_profile_iterator
  : boost::iterator_facade<application_profile_iterator<BaseIterator>
                           , application_profile<BaseIterator>
                           , boost::forward_traversal_tag
                           , application_profile<BaseIterator> >
{
  typedef application_profile_iterator<BaseIterator> self_type;

  application_profile_iterator() : base() {}
  application_profile_iterator(BaseIterator base)
  : base(base) {}

  void increment()
  {
    std::advance(base, application_profile<BaseIterator>
                 ::bits_size::value/CHAR_BIT);
  }
  bool equal(self_type const& other) const
  {
    return base == other.base;
  }
  application_profile<BaseIterator> dereference() const
  {
    return application_profile<BaseIterator>();
  }

  BaseIterator base;
};

}

// Defined in ETSI 102 809 v1.1.1 (2010-01) page 35
// and ABNT NBR 15606-3:2007 page 52
template <typename BaseIterator>
struct application_descriptor : tagged_descriptor<BaseIterator>
{
  typedef tagged_descriptor<BaseIterator> base_type;
  typedef application_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef application_descriptor_iterators::application_profiles_length_iterator<BaseIterator> application_profiles_length_iterator;
  typedef application_descriptor_iterators::application_profiles_iterator<BaseIterator> application_profiles_iterator;
  typedef application_descriptor_iterators::service_bound_flag_iterator<BaseIterator> service_bound_flag_iterator;
  typedef application_descriptor_iterators::visibility_iterator<BaseIterator> visibility_iterator;
  typedef application_descriptor_iterators::application_priority_iterator<BaseIterator> application_priority_iterator;
  typedef application_descriptor_iterators::transport_protocol_label_iterator<BaseIterator> transport_protocol_label_iterator;
  typedef application_descriptor_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  application_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  application_descriptor(base_type base)
    : base_type(base) {}
};

namespace application_descriptor_iterators {

template <typename BaseIterator>
struct after_application_profiles : application_descriptor<BaseIterator>
{
  typedef application_descriptor<BaseIterator> base_type;
  typedef BaseIterator base_iterator;

  after_application_profiles(BaseIterator first, base_type base)
    : base_type(base) {}

  base_iterator base_begin() const
  {
    return first;
  }

  BaseIterator first;
};

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , application_descriptor<BaseIterator>
                        , typename application_descriptor<BaseIterator>
                          ::application_profiles_length_iterator
                        >
  , offset_comparable, size_comparable
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef application_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , application_descriptor<BaseIterator>
                              , typename application_descriptor<BaseIterator>
                                ::application_profiles_length_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct application_profiles_length_iterator : static_offset_size_iterator
<application_profiles_length_iterator<BaseIterator>, BaseIterator
 , application_descriptor<BaseIterator>, boost::mpl::size_t<16u>
 , boost::mpl::size_t<8u>, unsigned int
 , application_profiles_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef application_descriptor<BaseIterator> sequence_type;

  application_profiles_length_iterator
  (sequence_type const& sequence
   , typename tagged_descriptor<BaseIterator>::data_iterator)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct application_profiles_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef application_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<application_descriptor_detail
                                ::application_profile_iterator<BaseIterator> >
    deref_type;
  typedef service_bound_flag_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;

  application_profiles_iterator(sequence_type const& sequence)
  : sequence(sequence)
  , length(*gts::iterators::next(sequence.begin()))
  {
    unsigned int max_length = std::distance(base(),sequence.base_end());
    if(length > max_length)
    {
      length = max_length - (max_length
                             % application_descriptor_detail
                             ::application_profile<BaseIterator>
                             ::bits_size::value/CHAR_BIT
                             );
    }
  }
  base_type base() const
  {
    return algorithm::position<bits_offset::value>
      (sequence.base_begin());
  }
  deref_type operator*() const
  {
    return deref_type(base(), boost::next(base(), length));
  }
  next_type operator++() const
  {
    return next_type(sequence, boost::next(base(), length));
  }

  sequence_type sequence;
  unsigned int length;
};

template <typename BaseIterator>
struct service_bound_flag_iterator : static_offset_size_iterator
<service_bound_flag_iterator<BaseIterator>, BaseIterator
 , after_application_profiles<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<1u>
 , bool, visibility_iterator<BaseIterator> >
{
  typedef application_descriptor<BaseIterator> outer_sequence_type;
  typedef after_application_profiles<BaseIterator> sequence_type;
  
  service_bound_flag_iterator(outer_sequence_type const& sequence
                              , BaseIterator first)
    : sequence(first, sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct visibility_iterator : static_offset_size_iterator
<visibility_iterator<BaseIterator>, BaseIterator
 , after_application_profiles<BaseIterator>
 , boost::mpl::size_t<1u>, boost::mpl::size_t<2u>
 , unsigned int, application_priority_iterator<BaseIterator> >
{
  typedef after_application_profiles<BaseIterator> sequence_type;
  
  visibility_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct application_priority_iterator : static_offset_size_iterator
<application_priority_iterator<BaseIterator>, BaseIterator
 , after_application_profiles<BaseIterator>
 , boost::mpl::size_t<8u>, boost::mpl::size_t<8u>
 , unsigned int, transport_protocol_label_iterator<BaseIterator> >
{
  typedef after_application_profiles<BaseIterator> sequence_type;
  
  application_priority_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct transport_protocol_label_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<16u> bits_offset;
  typedef after_application_profiles<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;
  
  transport_protocol_label_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  base_type base() const
  {
    return algorithm::position<bits_offset::value>(sequence.base_begin());
  }
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename application_descriptor<BaseIterator>::begin_iterator
application_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

// template <typename BaseIterator>
// typename application_iterator<BaseIterator>::end_iterator
// application_iterator<BaseIterator>::end() const
// {
// }

} }

#endif
