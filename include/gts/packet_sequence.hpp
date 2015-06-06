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

#ifndef GTS_PACKET_SEQUENCE_HPP
#define GTS_PACKET_SEQUENCE_HPP

#include <gts/adaptation_field_sequence.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/sequences/sequence_concept.hpp>

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

namespace packet_iterators {

template <typename BaseIterator>
struct sync_byte_iterator;

template <typename BaseIterator>
struct transport_error_indicator_iterator;

template <typename BaseIterator>
struct transport_error_indicator_iterator;

template <typename BaseIterator>
struct payload_unit_start_indicator_iterator;

template <typename BaseIterator>
struct transport_priority_iterator;

template <typename BaseIterator>
struct pid_iterator;

template <typename BaseIterator>
struct transport_scrambling_control_iterator;

template <typename BaseIterator>
struct adaptation_field_control_iterator;

template <typename BaseIterator>
struct continuity_counter_iterator;

template <typename BaseIterator>
struct adaptation_field_iterator;

template <typename BaseIterator>
struct payload_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct packet_sequence
{
  packet_sequence(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef packet_iterators::sync_byte_iterator<BaseIterator> sync_byte_iterator;
  typedef packet_iterators::transport_error_indicator_iterator<BaseIterator> transport_error_indicator_iterator;
  typedef packet_iterators::payload_unit_start_indicator_iterator<BaseIterator>
    payload_unit_start_indicator_iterator;
  typedef packet_iterators::transport_priority_iterator<BaseIterator> transport_priority_iterator;
  typedef packet_iterators::pid_iterator<BaseIterator> pid_iterator;
  typedef packet_iterators::transport_scrambling_control_iterator<BaseIterator>
    transport_scrambling_control_iterator;
  typedef packet_iterators::adaptation_field_control_iterator<BaseIterator>
    adaptation_field_control_iterator;
  typedef packet_iterators::continuity_counter_iterator<BaseIterator> continuity_counter_iterator;
  typedef packet_iterators::adaptation_field_iterator<BaseIterator> adaptation_field_iterator;
  typedef packet_iterators::payload_iterator<BaseIterator> payload_iterator;
  typedef sync_byte_iterator begin_iterator;
  typedef packet_iterators::end_iterator<BaseIterator> end_iterator;

  typedef BaseIterator base_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

template <typename BaseIterator>
bool operator==(packet_sequence<BaseIterator> const& lhs, packet_sequence<BaseIterator> const& rhs)
{
  return (lhs.first == rhs.first
          && lhs.last == rhs.last)
    || (std::distance(lhs.first, lhs.last) == std::distance(rhs.first, rhs.last)
        && std::equal(lhs.first, lhs.last, rhs.first));
}

template <typename BaseIterator>
bool operator!=(packet_sequence<BaseIterator> const& lhs, packet_sequence<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

namespace packet_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct sync_byte_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef boost::uint_t<8u>::least deref_type;

  sync_byte_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef transport_error_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct transport_error_indicator_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  transport_error_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef payload_unit_start_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct payload_unit_start_indicator_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<9u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  payload_unit_start_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef transport_priority_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct transport_priority_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<10u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  transport_priority_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef pid_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct pid_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<11u> bits_offset;
  typedef boost::mpl::size_t<13u> bits_size;
  typedef std::size_t deref_type;

  pid_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef transport_scrambling_control_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct transport_scrambling_control_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef boost::mpl::size_t<2u> bits_size;
  typedef std::size_t deref_type;

  transport_scrambling_control_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef adaptation_field_control_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct adaptation_field_control_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<26u> bits_offset;
  typedef boost::mpl::size_t<2u> bits_size;
  typedef std::size_t deref_type;

  adaptation_field_control_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef continuity_counter_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct continuity_counter_iterator : offset_comparable, size_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<28u> bits_offset;
  typedef boost::mpl::size_t<4u> bits_size;
  typedef std::size_t deref_type;

  continuity_counter_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef adaptation_field_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct adaptation_field_iterator : offset_comparable
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_offset;
  typedef gts::adaptation_field_sequence<BaseIterator> deref_type;

  adaptation_field_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    typedef packet_iterators::adaptation_field_control_iterator<BaseIterator> adaptation_field_control_iterator;
    adaptation_field_control_iterator adaptation_field_control(sequence);
    assert((*adaptation_field_control & 2) == 2);
    typedef gts::adaptation_field_sequence<BaseIterator> adaptation_field_type;
    BOOST_MPL_ASSERT_RELATION(bits_offset::value % CHAR_BIT, ==, 0);
    BaseIterator first = boost::next(sequence.first, bits_offset::value/CHAR_BIT);
    return adaptation_field_type (first, sequence.last);
  }
  typedef payload_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    typedef packet_iterators::adaptation_field_control_iterator<BaseIterator> adaptation_field_control_iterator;
    adaptation_field_control_iterator adaptation_field_control(sequence);
    if((*adaptation_field_control & 2) == 2)
    {
      deref_type deref = **this;
      return next_type(sequence, deref.end().base());
    }
    else
      return next_type(sequence, boost::next(sequence.first, bits_offset::value/CHAR_BIT));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct payload_iterator
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef std::pair<BaseIterator, BaseIterator> deref_type;

  payload_iterator(sequence_type const& sequence, BaseIterator payload_start)
    : sequence(sequence), payload_start(payload_start) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return payload_start; }
  deref_type operator*() const
  {
    return std::make_pair(payload_start, sequence.last);
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
  BaseIterator payload_start;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef packet_sequence<BaseIterator> sequence_type;
  typedef BaseIterator deref_type;

  end_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::stationary_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  base_type base() const { return sequence.last; }

  sequence_type const& sequence;
};

template <typename BaseIterator>
bool operator==(payload_iterator<BaseIterator>, payload_iterator<BaseIterator>)
{
  return true;
}

template <typename BaseIterator>
bool operator!=(payload_iterator<BaseIterator>, payload_iterator<BaseIterator>)
{
  return false;
}

template <typename BaseIterator>
bool operator==(adaptation_field_iterator<BaseIterator>, payload_iterator<BaseIterator>)
{
  return false;
}

template <typename BaseIterator>
bool operator==(payload_iterator<BaseIterator>, adaptation_field_iterator<BaseIterator>)
{
  return false;
}

template <typename BaseIterator>
bool operator!=(payload_iterator<BaseIterator>, adaptation_field_iterator<BaseIterator>)
{
  return true;
}

template <typename BaseIterator>
bool operator!=(adaptation_field_iterator<BaseIterator>, payload_iterator<BaseIterator>)
{
  return true;
}

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator>
                , packet_iterators::adaptation_field_iterator<BaseIterator> iterator)
{
  typedef packet_iterators::adaptation_field_iterator<BaseIterator> adaptation_field_iterator;
  BOOST_MPL_ASSERT_RELATION(adaptation_field_iterator::bits_offset::value % CHAR_BIT, ==, 0);
  BaseIterator first = boost::next(iterator.sequence.first
                                   , adaptation_field_iterator::bits_offset::value / CHAR_BIT);
  if(std::distance(first, iterator.sequence.last) >= 1)
  {
    typedef gts::adaptation_field_sequence<BaseIterator> adaptation_field_type;
    adaptation_field_type adaptation_field(first, iterator.sequence.last);
    typedef typename adaptation_field_type::adaptation_field_length_iterator adaptation_field_length_iterator;
    adaptation_field_length_iterator adaptation_field_length = adaptation_field.begin();
    std::size_t distance = std::distance(first, iterator.sequence.last);
    return distance < *adaptation_field_length + 1;
  }
  else
    return true;
}

template <typename BaseIterator>
bool operator==(adaptation_field_iterator<BaseIterator> adaptation_field, end_iterator<BaseIterator> end)
{
  return end == adaptation_field;
}

template <typename BaseIterator>
bool operator!=(adaptation_field_iterator<BaseIterator> adaptation_field, end_iterator<BaseIterator> end)
{
  return !(end == adaptation_field);
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> end, adaptation_field_iterator<BaseIterator> adaptation_field)
{
  return !(end == adaptation_field);
}

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator>
                , packet_iterators::payload_iterator<BaseIterator> iterator)
{
  return iterator.payload_start == iterator.sequence.last;
}

template <typename BaseIterator>
bool operator==(packet_iterators::payload_iterator<BaseIterator> iterator
                , end_iterator<BaseIterator> end)
{
  return end == iterator;
}

template <typename BaseIterator>
bool operator!=(packet_iterators::payload_iterator<BaseIterator> iterator
                , end_iterator<BaseIterator> end)
{
  return !(end == iterator);
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> end
                , packet_iterators::payload_iterator<BaseIterator> iterator)
{
  return !(end == iterator);
}

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
<boost::mpl::and_
  <boost::is_convertible<OffsetSizeIterator, offset_comparable>
   , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator==(end_iterator<BaseIterator> end, OffsetSizeIterator offset_iterator)
{
  std::size_t distance = std::distance(end.sequence.first, end.sequence.last);
  const std::size_t bits = OffsetSizeIterator::bits_offset::value + OffsetSizeIterator::bits_size::value;
  return distance < (bits/CHAR_BIT) + (bits%CHAR_BIT?1:0);
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_
  <boost::is_convertible<OffsetSizeIterator, offset_comparable>
   , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator==(OffsetSizeIterator offset_iterator, end_iterator<BaseIterator> end)
{
  return (end == offset_iterator);
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_
  <boost::is_convertible<OffsetSizeIterator, offset_comparable>
   , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator!=(OffsetSizeIterator offset_iterator, end_iterator<BaseIterator> end)
{
  return !(end == offset_iterator);
}

template <typename BaseIterator, typename OffsetSizeIterator>
typename boost::enable_if
<boost::mpl::and_
  <boost::is_convertible<OffsetSizeIterator, offset_comparable>
   , boost::is_convertible<OffsetSizeIterator, size_comparable> >
 , bool>::type
operator!=(end_iterator<BaseIterator> end, OffsetSizeIterator offset_iterator)
{
  return !(end == offset_iterator);
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
typename packet_sequence<BaseIterator>::begin_iterator packet_sequence<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename packet_sequence<BaseIterator>::end_iterator packet_sequence<BaseIterator>::end() const
{
  return end_iterator(*this);
}

}

#endif
