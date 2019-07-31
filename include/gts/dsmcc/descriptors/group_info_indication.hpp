///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DESCRIPTORS_GROUP_INFO_INDICATION_HPP
#define GTS_DSMCC_DESCRIPTORS_GROUP_INFO_INDICATION_HPP

#include <gts/dsmcc/descriptors/group_info.hpp>

namespace gts { namespace dsmcc { namespace descriptors {

namespace group_info_indication_iterators {

template <typename BaseIterator>
struct groups_iterator;

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct group_info_indication
{
  typedef group_info_indication_iterators::groups_iterator<BaseIterator> groups_iterator;
  typedef group_info_indication_iterators::private_data_iterator<BaseIterator> private_data_iterator;
  typedef groups_iterator begin_iterator;
  typedef group_info_indication_iterators::end_iterator<BaseIterator> end_iterator;  

  group_info_indication(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator base_begin() const { return first; }
  BaseIterator base_end() const { return last; }

  BaseIterator first, last;
};

namespace group_info_indication_iterators {

template <typename BaseIterator>
struct group_info_iterator : boost::iterator_facade
  <group_info_iterator<BaseIterator>
   , group_info<BaseIterator>
   , boost::forward_traversal_tag
   , group_info<BaseIterator> >
{
  group_info_iterator(BaseIterator first, BaseIterator last
                      , unsigned int current_index, unsigned int last_index)
    : current(first), last(last), current_index(current_index)
    , last_index(last_index) {}

  void increment()
  {
    ++current_index;
  }
  group_info<BaseIterator> dereference() const;
  bool equal(group_info_iterator<BaseIterator> const& other) const
  {
    return current == other.current || current_index == other.current_index;
  }

  BaseIterator current, last;
  unsigned int current_index, last_index;
};

template <typename BaseIterator>
struct groups_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::iterator_range<group_info_iterator<BaseIterator> > deref_type;
  typedef group_info_indication<BaseIterator> sequence_type;
  typedef end_iterator<BaseIterator> next_type;

  groups_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  deref_type operator*() const
  {
    BaseIterator first = sequence.base_begin(), last = sequence.base_end();
    boost::uint_t<16u>::exact number_of_groups
      = algorithm::parse_data<boost::uint_t<16u>::exact, 0u, 16u>(first);
    first = algorithm::position<16u>(first);
    group_info_iterator<BaseIterator> first_group(first, last, 0u, number_of_groups)
      , last_group(first, last, number_of_groups, number_of_groups);
    return deref_type(first_group, last_group);
  }
  next_type operator++() const;

  sequence_type sequence;
};

}

template <typename BaseIterator>
typename group_info_indication<BaseIterator>::begin_iterator group_info_indication<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename group_info_indication<BaseIterator>::end_iterator group_info_indication<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
