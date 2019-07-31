///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SECTIONS_PRIVATE_SECTION_HPP
#define GTS_SECTIONS_PRIVATE_SECTION_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace sections {

namespace private_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_indicator_iterator;

template <typename BaseIterator>
struct private_indicator_iterator;

template <typename BaseIterator>
struct private_section_length_iterator;

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct private_section
{
  private_section(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef private_section_iterators::table_id_iterator<BaseIterator> table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef private_section_iterators::section_syntax_indicator_iterator<BaseIterator>
    section_syntax_indicator_iterator;
  typedef private_section_iterators::private_indicator_iterator<BaseIterator>
    private_indicator_iterator;
  typedef private_section_iterators::private_section_length_iterator<BaseIterator>
    private_section_length_iterator;
  typedef private_section_iterators::private_data_iterator<BaseIterator> private_data_iterator;
  typedef private_section_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;

  typedef BaseIterator base_iterator;

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  BaseIterator first, last;
};

namespace private_section_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct table_id_iterator : offset_comparable, size_comparable
{
  typedef private_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;

  table_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef section_syntax_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_syntax_indicator_iterator : offset_comparable, size_comparable
{
  typedef private_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  section_syntax_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef private_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct private_indicator_iterator : offset_comparable, size_comparable
{
  typedef private_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<9u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  private_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef private_section_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct private_section_length_iterator : offset_comparable, size_comparable
{
  typedef private_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<12u> bits_offset;
  typedef boost::mpl::size_t<12u> bits_size;
  typedef unsigned int deref_type;

  private_section_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef private_data_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct private_data_iterator : offset_comparable
{
  typedef private_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;

  private_data_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return deref_type(base (), sequence.last);
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

}

template <typename BaseIterator>
typename private_section<BaseIterator>::begin_iterator
private_section<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

} }

#endif
