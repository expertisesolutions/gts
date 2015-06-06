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

#ifndef GTS_SDT_PRIVATE_HPP
#define GTS_SDT_PRIVATE_HPP

#include <gts/partial_descriptor_sequence.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/descriptor_private_range.hpp>
#include <gts/static_offset_size_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts {

namespace sdt_private_iterators {

template <typename BaseIterator>
struct original_network_identifier_iterator;

template <typename BaseIterator>
struct services_iterator;

template <typename BaseIterator>
struct end_iterator;

}

namespace sdt_private_detail {

namespace service_iterators {

template <typename BaseIterator>
struct service_identifier_iterator;

template <typename BaseIterator>
struct eit_schedule_flag_iterator;

template <typename BaseIterator>
struct eit_present_following_flag_iterator;

template <typename BaseIterator>
struct running_status_iterator;

template <typename BaseIterator>
struct free_ca_mode_iterator;

template <typename BaseIterator>
struct descriptors_loop_length_iterator;

template <typename BaseIterator>
struct descriptors_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct service
{
  service() {}

  typedef BaseIterator base_iterator;
  service(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef service_iterators::service_identifier_iterator<BaseIterator> service_identifier_iterator;
  typedef service_identifier_iterator begin_iterator;
  typedef service_iterators::eit_schedule_flag_iterator<BaseIterator> eit_schedule_flag_iterator;
  typedef service_iterators::eit_present_following_flag_iterator<BaseIterator> eit_present_following_flag_iterator;
  typedef service_iterators::running_status_iterator<BaseIterator> running_status_iterator;
  typedef service_iterators::free_ca_mode_iterator<BaseIterator> free_ca_mode_iterator;
  typedef service_iterators::descriptors_loop_length_iterator<BaseIterator> descriptors_loop_length_iterator;
  typedef service_iterators::descriptors_iterator<BaseIterator> descriptors_iterator;
  typedef service_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }
  
  BaseIterator first, last;
};

template <typename BaseIterator>
struct service_range
{

  struct iterator : boost::iterator_facade<iterator, service<BaseIterator>, boost::forward_traversal_tag, service<BaseIterator> >
  {
    iterator ()
    {
    }
    iterator(BaseIterator first, BaseIterator last)
      : service_(first, last), last(last)
    {
      typedef typename service<BaseIterator>::descriptors_loop_length_iterator
        descriptors_loop_length_iterator;
      typedef typename service<BaseIterator>::descriptors_iterator
        descriptors_iterator;
      descriptors_loop_length_iterator it = gts::iterators::next<5>(service_.begin());
      service_.last = boost::next(first, *it + (descriptors_iterator::bits_offset::value/CHAR_BIT));
    }

    bool equal(iterator const& other) const
    {
      return service_.base_begin() == other.service_.base_begin();
    }
    void increment()
    {
      service_.first = service_.last;
      service_.last = last;
      typedef typename service<BaseIterator>::descriptors_loop_length_iterator
        descriptors_loop_length_iterator;
      typedef typename service<BaseIterator>::descriptors_iterator
        descriptors_iterator;
      descriptors_loop_length_iterator it = gts::iterators::next<5>(service_.begin());
      service_.last = boost::next(service_.first
                                  , *it + (descriptors_iterator::bits_offset::value/CHAR_BIT));
    }
    service<BaseIterator> dereference() const
    {
      return service_;
    }

    service<BaseIterator> service_;
    BaseIterator last;
  };
  typedef iterator const_iterator;

  iterator begin () const
  {
    return iterator(first, last);
  }
  iterator end () const
  {
    return iterator(last, last);
  }

  service_range(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;

  base_iterator base_begin() const
  {
    return first;
  }
  base_iterator base_end() const
  {
    return last;
  }

  BaseIterator first, last;
};

namespace service_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct service_identifier_iterator : static_offset_size_iterator
<service_identifier_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<0u>, boost::mpl::size_t<16u>
 , unsigned int, eit_schedule_flag_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  service_identifier_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct eit_schedule_flag_iterator : static_offset_size_iterator
<eit_schedule_flag_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<22u>, boost::mpl::size_t<1u>
 , bool, eit_present_following_flag_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  eit_schedule_flag_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct eit_present_following_flag_iterator : static_offset_size_iterator
<eit_present_following_flag_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<23u>, boost::mpl::size_t<1u>
 , bool, running_status_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  eit_present_following_flag_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct running_status_iterator : static_offset_size_iterator
<running_status_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<24u>, boost::mpl::size_t<3u>
 , unsigned int, free_ca_mode_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  running_status_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct free_ca_mode_iterator : static_offset_size_iterator
<free_ca_mode_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<27u>, boost::mpl::size_t<1u>
 , unsigned int, descriptors_loop_length_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  free_ca_mode_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct descriptors_loop_length_iterator : static_offset_size_iterator
<descriptors_loop_length_iterator<BaseIterator>, BaseIterator
 , service<BaseIterator>, boost::mpl::size_t<28u>, boost::mpl::size_t<12u>
 , unsigned int, descriptors_iterator<BaseIterator> >
  , offset_comparable, size_comparable
{
  typedef service<BaseIterator> sequence_type;
  
  descriptors_loop_length_iterator(sequence_type const& s)
  : sequence(s) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct descriptors_iterator : offset_comparable
{
  typedef boost::mpl::size_t<40u> bits_offset;
  typedef service<BaseIterator> sequence_type;
  typedef descriptor_private_range<BaseIterator> deref_type;

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;

  descriptors_iterator(sequence_type const& sequence)
  : sequence(sequence) {}

  std::size_t size() const
  {
    return *gts::iterators::next<5>(sequence.begin());
  }
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); } 
  deref_type operator*() const
  {
    return deref_type(base(), boost::next(base(), size()));
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename service<BaseIterator>::begin_iterator service<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

}

template <typename BaseIterator>
struct sdt_private
{
  sdt_private(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef sdt_private_iterators::original_network_identifier_iterator<BaseIterator>
    original_network_identifier_iterator;
  typedef original_network_identifier_iterator begin_iterator;
  typedef sdt_private_iterators::services_iterator<BaseIterator> services_iterator;
  typedef sdt_private_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  BaseIterator first, last;
};

namespace sdt_private_iterators {

template <typename BaseIterator>
struct original_network_identifier_iterator
{
  typedef sdt_private<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef unsigned int deref_type;

  original_network_identifier_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef services_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct services_iterator
{
  typedef sdt_private<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef sdt_private_detail::service_range<BaseIterator> deref_type;

  services_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return deref_type(boost::next(sequence.base_begin(), bits_offset::value/CHAR_BIT)
                      , sequence.base_end());
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(boost::next(sequence.base_begin(), bits_offset::value/CHAR_BIT)
                     , sequence.base_end());
  }

  sequence_type sequence;  
};

}

template <typename BaseIterator>
typename sdt_private<BaseIterator>::begin_iterator sdt_private<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

}

#endif
