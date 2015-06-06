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

#ifndef GTS_ADAPTATION_FIELD_SEQUENCE_HPP
#define GTS_ADAPTATION_FIELD_SEQUENCE_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/sequences/sequence_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/next.hpp>

#include <boost/integer.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/utility.hpp>
#include <climits>
#include <algorithm>

namespace gts {

namespace adaptation_field_iterators {

template <typename BaseIterator>
struct adaptation_field_length_iterator;

template <typename BaseIterator>
struct discontinuity_indicator_iterator;

template <typename BaseIterator>
struct random_access_indicator_iterator;

template <typename BaseIterator>
struct elementary_stream_priority_indicator_iterator;

template <typename BaseIterator>
struct pcr_flag_iterator;

template <typename BaseIterator>
struct opcr_flag_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct adaptation_field_sequence
{
  adaptation_field_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {
    assert(std::distance(first, last) >= 1);
    length = *begin_iterator(*this)+1;
  }

  typedef adaptation_field_iterators::adaptation_field_length_iterator<BaseIterator>
    adaptation_field_length_iterator;
  typedef adaptation_field_iterators::discontinuity_indicator_iterator<BaseIterator>
    discontinuity_indicator_iterator;
  typedef adaptation_field_iterators::random_access_indicator_iterator<BaseIterator>
    random_access_indicator_iterator;
  typedef adaptation_field_iterators::pcr_flag_iterator<BaseIterator> pcr_flag_iterator;
  typedef adaptation_field_iterators::opcr_flag_iterator<BaseIterator> opcr_flag_iterator;
  typedef adaptation_field_length_iterator begin_iterator;
  typedef adaptation_field_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
  std::size_t length;
};

namespace adaptation_field_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct adaptation_field_length_iterator : offset_comparable, size_comparable
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef std::size_t deref_type;

  adaptation_field_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef discontinuity_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct discontinuity_indicator_iterator : offset_comparable, size_comparable
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  discontinuity_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef random_access_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct random_access_indicator_iterator : offset_comparable, size_comparable
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<9u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  random_access_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef elementary_stream_priority_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct elementary_stream_priority_indicator_iterator
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<10u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  elementary_stream_priority_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef pcr_flag_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct pcr_flag_iterator
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<11u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  pcr_flag_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef opcr_flag_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct opcr_flag_iterator
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<12u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  opcr_flag_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  // typedef opcr_flag_iterator<BaseIterator> next_type;
  // next_type operator++() const
  // {
  //   return next_type(sequence);
  // }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef adaptation_field_sequence<BaseIterator> sequence_type;

  end_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::stationary_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const
  {
    std::size_t distance = std::distance(sequence.first, sequence.last);
    if(distance >= sequence.length)
      return boost::next(sequence.first, sequence.length);
    else
      return sequence.last;
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator>, end_iterator<BaseIterator>)
{
  return true;
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> lhs, end_iterator<BaseIterator> rhs)
{
  return !(lhs == rhs);
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<OffsetSizeIterator, offset_comparable>
                  , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator==(end_iterator<BaseIterator> end, OffsetSizeIterator offset_size_iterator)
{
  std::size_t max_size = std::distance(end.sequence.first, end.sequence.last);
  BaseIterator last = max_size > end.sequence.length
    ?boost::next(end.sequence.first, end.sequence.length):end.sequence.last;
  std::size_t const bits = OffsetSizeIterator::bits_offset::value + OffsetSizeIterator::bits_size::value;
  std::size_t const bytes = (bits/CHAR_BIT) + (bits % CHAR_BIT ? 1 : 0);
  std::size_t distance = std::distance(end.sequence.first, last);
  return distance < bytes;
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<OffsetSizeIterator, offset_comparable>
                  , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator==(OffsetSizeIterator offset_size_iterator, end_iterator<BaseIterator> end)
{
  return end == offset_size_iterator;
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<OffsetSizeIterator, offset_comparable>
                  , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator!=(OffsetSizeIterator offset_size_iterator, end_iterator<BaseIterator> end)
{
  return !(end == offset_size_iterator);
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<OffsetSizeIterator, offset_comparable>
                  , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator!=(end_iterator<BaseIterator> end, OffsetSizeIterator offset_size_iterator)
{
  return !(end == offset_size_iterator);
}

template <typename Iterator1, typename Iterator2>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<Iterator1, offset_comparable>
                  , boost::is_convertible<Iterator2, offset_comparable> >
 , bool>::type
operator==(Iterator1 lhs, Iterator2 rhs)
{
  return Iterator1::bits_offset::value == Iterator2::bits_offset::value;
}

template <typename Iterator>
typename boost::enable_if
<boost::is_convertible<Iterator, offset_comparable>, bool>::type
operator==(Iterator lhs, Iterator rhs)
{
  return true;
}

template <typename Iterator1, typename Iterator2>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<Iterator1, offset_comparable>
                  , boost::is_convertible<Iterator2, offset_comparable> >
 , bool>::type
operator!=(Iterator1 lhs, Iterator2 rhs)
{
  return !(lhs == rhs);
}

}

template <typename BaseIterator>
typename adaptation_field_sequence<BaseIterator>::begin_iterator
adaptation_field_sequence<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename adaptation_field_sequence<BaseIterator>::end_iterator
adaptation_field_sequence<BaseIterator>::end() const
{
  return end_iterator(*this);
}

}

#endif
