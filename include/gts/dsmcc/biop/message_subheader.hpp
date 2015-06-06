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

#ifndef GTS_DSMCC_BIOP_MESSAGE_SUBHEADER_HPP
#define GTS_DSMCC_BIOP_MESSAGE_SUBHEADER_HPP

#include <gts/base_sequence.hpp>
#include <gts/dsmcc/biop/service_context_list_iterator.hpp>
#include <gts/dsmcc/biop/object_info_iterator.hpp>

namespace gts { namespace dsmcc { namespace biop {

namespace message_subheader_detail {

template <typename BaseIterator>
struct object_kind_internal_sequence : base_sequence<BaseIterator>
{
  object_kind_internal_sequence(BaseIterator first, BaseIterator last)
    : base_sequence<BaseIterator>(first, last)
  {}
};

template <typename BaseIterator>
struct object_info_internal_sequence : base_sequence<BaseIterator>
{
  object_info_internal_sequence(BaseIterator first, BaseIterator last)
    : base_sequence<BaseIterator>(first, last)
  {}
};

template <typename BaseIterator>
struct service_context_list_internal_sequence : base_sequence<BaseIterator>
{
  service_context_list_internal_sequence(BaseIterator first, BaseIterator last)
    : base_sequence<BaseIterator>(first, last)
  {}
};

template <typename BaseIterator>
struct end_internal_sequence
{
  end_internal_sequence(BaseIterator first, BaseIterator last)
    : first(first)
  {}

  typedef BaseIterator base_iterator;
  BaseIterator base_begin() const { return first; }
  BaseIterator base_end() const { return first; }

  BaseIterator first;
};

}

namespace message_subheader_iterators {

template <typename BaseIterator>
struct object_key_iterator;

template <typename BaseIterator>
struct object_kind_iterator;

template <typename BaseIterator>
struct object_info_iterator;

template <typename BaseIterator>
struct service_context_list_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 309
template <typename BaseIterator>
struct message_subheader
{
  typedef message_subheader_iterators::object_key_iterator<BaseIterator> object_key_iterator;
  typedef object_key_iterator begin_iterator;
  typedef message_subheader_iterators::object_kind_iterator<BaseIterator> object_kind_iterator;
  typedef message_subheader_iterators::object_info_iterator<BaseIterator> object_info_iterator;
  typedef message_subheader_iterators::end_iterator<BaseIterator> end_iterator;
  typedef biop::service_context_list_iterator
    <BaseIterator
     , message_subheader_detail::service_context_list_internal_sequence<BaseIterator>
     , end_iterator
     , message_subheader_detail::end_internal_sequence<BaseIterator> >
    service_context_list_iterator;

  typedef BaseIterator base_iterator;
  message_subheader(base_iterator first, base_iterator last)
    : first(first), last(last) {}

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  base_iterator first, last;
};

namespace message_subheader_iterators {

template <typename BaseIterator>
struct object_key_iterator : static_offset_size_iterator
<object_key_iterator<BaseIterator>, BaseIterator, message_subheader<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<8u> /* key size */, boost::uint_t<8u>::least
 , object_kind_iterator<BaseIterator> >
{
  typedef message_subheader<BaseIterator> sequence_type;
  typedef static_offset_size_iterator
  <object_key_iterator<BaseIterator>, BaseIterator, message_subheader<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<8u> /* key size */, boost::uint_t<8u>::least
   , object_kind_iterator<BaseIterator> > base_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef typename base_type::next_type next_type;

  object_key_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  deref_type operator* () const
  {
    typedef typename base_type::bits_size bits_size;
    typename base_type::deref_type size = base_type::operator*();
    //std::cout << "object_key_iterator::size = " << (int)size << std::endl;
    BaseIterator first = algorithm::position<bits_size::value>(this->base())
      , last = sequence.base_end();
    if(std::distance(first, last) > size)
      last = boost::next(first, size);
    return deref_type(first, last);
  }
  next_type operator++() const
  {
    typedef typename base_type::bits_size bits_size;
    typename base_type::deref_type size = base_type::operator*();
    BaseIterator first = algorithm::position<bits_size::value>(this->base())
      , next = sequence.base_end()
      , last = sequence.base_end();
    if(std::distance(first, next) > size)
      next = boost::next(first, size);
    typedef message_subheader_detail::object_kind_internal_sequence<BaseIterator> next_sequence;
    return next_type(next_sequence(next, last));
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct object_kind_iterator : static_offset_size_iterator
<object_kind_iterator<BaseIterator>, BaseIterator
 , message_subheader_detail::object_kind_internal_sequence<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<32u> /* key size */, boost::uint_t<32u>::least
 , object_info_iterator<BaseIterator> >
{
  typedef message_subheader_detail::object_kind_internal_sequence<BaseIterator> sequence_type;
  typedef static_offset_size_iterator
  <object_kind_iterator<BaseIterator>, BaseIterator
   , message_subheader_detail::object_kind_internal_sequence<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<32u> /* key size */, boost::uint_t<32u>::least
   , object_info_iterator<BaseIterator> > base_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef typename base_type::next_type next_type;

  object_kind_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  deref_type operator* () const
  {
    typedef typename base_type::bits_size bits_size;
    typename base_type::deref_type size = base_type::operator*();
    BaseIterator first = algorithm::position<bits_size::value>(this->base())
      , last = sequence.base_end();
    if(std::distance(first, last) > size)
      last = boost::next(first, size);
    return deref_type(first, last);
  }
  next_type operator++() const
  {
    typedef typename base_type::bits_size bits_size;
    typename base_type::deref_type size = base_type::operator*();
    BaseIterator first = algorithm::position<bits_size::value>(this->base())
      , next = sequence.base_end()
      , last = sequence.base_end();
    if(std::distance(first, next) > size)
      next = boost::next(first, size);
    typedef message_subheader_detail::object_info_internal_sequence<BaseIterator> next_sequence;
    return next_type(next_sequence(next, last));
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct object_info_iterator
  : biop::object_info_iterator<BaseIterator, message_subheader_detail::object_info_internal_sequence<BaseIterator>
                               , typename message_subheader<BaseIterator>::service_context_list_iterator
                               , message_subheader_detail::service_context_list_internal_sequence<BaseIterator> >
{
  typedef biop::object_info_iterator<BaseIterator, message_subheader_detail::object_info_internal_sequence<BaseIterator>
                                     , typename message_subheader<BaseIterator>::service_context_list_iterator
                                     , message_subheader_detail::service_context_list_internal_sequence<BaseIterator> > base_type;
  object_info_iterator(typename base_type::sequence_type const& sequence)
    : base_type(sequence) {}
};

template <typename BaseIterator>
struct end_iterator
{
  typedef message_subheader_detail::end_internal_sequence<BaseIterator> sequence_type;

  end_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef BaseIterator base_type;
  base_type base() const { return sequence.first; }

  sequence_type sequence;
};

}

template <typename BaseIterator>
typename message_subheader<BaseIterator>::begin_iterator message_subheader<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename message_subheader<BaseIterator>::end_iterator message_subheader<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
