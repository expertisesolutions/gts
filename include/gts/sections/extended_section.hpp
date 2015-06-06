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

#ifndef GTS_SECTIONS_EXTENDED_SECTION_HPP
#define GTS_SECTIONS_EXTENDED_SECTION_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace sections {

namespace extended_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_indicator_iterator;

template <typename BaseIterator>
struct private_indicator_iterator;

template <typename BaseIterator>
struct private_section_length_iterator;

template <typename BaseIterator>
struct table_id_extension_iterator;

template <typename BaseIterator>
struct version_number_iterator;

template <typename BaseIterator>
struct current_next_indicator_iterator;

template <typename BaseIterator>
struct section_number_iterator;

template <typename BaseIterator>
struct last_section_number_iterator;

template <typename BaseIterator>
struct private_data_iterator;

template <typename BaseIterator>
struct crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct extended_section
{
  extended_section(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  typedef extended_section_iterators::table_id_iterator<BaseIterator> table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef extended_section_iterators::section_syntax_indicator_iterator<BaseIterator>
    section_syntax_indicator_iterator;
  typedef extended_section_iterators::private_indicator_iterator<BaseIterator> private_indicator_iterator;
  typedef extended_section_iterators::private_section_length_iterator<BaseIterator> 
    private_section_length_iterator;
  typedef extended_section_iterators::table_id_extension_iterator<BaseIterator>
    table_id_extension_iterator;
  typedef extended_section_iterators::version_number_iterator<BaseIterator> version_number_iterator;
  typedef extended_section_iterators::current_next_indicator_iterator<BaseIterator>
    current_next_indicator_iterator;
  typedef extended_section_iterators::section_number_iterator<BaseIterator> section_number_iterator;
  typedef extended_section_iterators::last_section_number_iterator<BaseIterator> last_section_number_iterator;
  typedef extended_section_iterators::private_data_iterator<BaseIterator> private_data_iterator;
  typedef extended_section_iterators::crc32_iterator<BaseIterator> crc32_iterator;
  typedef extended_section_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;

  BaseIterator first, last;  
};

template <typename BaseIterator>
bool operator==(extended_section<BaseIterator> const& lhs
                , extended_section<BaseIterator> const& rhs)
{
  return (lhs.first == rhs.first && lhs.last == rhs.last)
    || (std::distance(lhs.first, lhs.last) == std::distance(rhs.first, rhs.last)
        && std::equal(lhs.first, lhs.last, rhs.first));
}

template <typename BaseIterator>
bool operator!=(extended_section<BaseIterator> const& lhs
                , extended_section<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

namespace extended_section_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct table_id_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef std::size_t deref_type;

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
  typedef extended_section<BaseIterator> sequence_type;
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
  typedef extended_section<BaseIterator> sequence_type;
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
  typedef extended_section<BaseIterator> sequence_type;
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
  typedef table_id_extension_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct table_id_extension_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef unsigned int deref_type;

  table_id_extension_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef version_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct version_number_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<42u> bits_offset;
  typedef boost::mpl::size_t<5u> bits_size;
  typedef unsigned int deref_type;

  version_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef current_next_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct current_next_indicator_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<47u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  current_next_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_number_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<48u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;

  section_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef last_section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct last_section_number_iterator : offset_comparable, size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<56u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef unsigned int deref_type;

  last_section_number_iterator(sequence_type const& sequence)
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
    return next_type(sequence, *gts::iterators::next
                     (gts::iterators::next
                      (gts::iterators::next(sequence.begin()))));
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct private_data_iterator : offset_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<64u> bits_offset;
  typedef boost::iterator_range<BaseIterator> deref_type;

  private_data_iterator(sequence_type const& sequence, unsigned int private_section_length)
    : sequence(sequence), private_section_length(private_section_length) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return deref_type(boost::next(sequence.first, bits_offset::value/CHAR_BIT)
                      , boost::next
                      (sequence.first
                       , private_section_length - 1));
  }
  typedef private_data_iterator<BaseIterator> next_type;
  next_type operator++() const;

  sequence_type sequence;  
  unsigned int private_section_length;
};

template <typename BaseIterator>
struct crc32_iterator : size_comparable
{
  typedef extended_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef boost::iterator_range<BaseIterator> deref_type;

  crc32_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const;// { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const;
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const;

  sequence_type sequence;  
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename extended_section<BaseIterator>::begin_iterator
extended_section<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename extended_section<BaseIterator>::end_iterator
extended_section<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} }

#endif
