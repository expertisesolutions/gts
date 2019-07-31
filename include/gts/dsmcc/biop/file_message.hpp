///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_FILE_MESSAGE_HPP
#define GTS_DSMCC_BIOP_FILE_MESSAGE_HPP

#include <gts/dsmcc/biop/file_object_info.hpp>
#include <gts/dsmcc/biop/file_message_body.hpp>
#include <gts/dsmcc/biop/object_info_iterator.hpp>
#include <gts/dsmcc/biop/service_context_list_iterator.hpp>
#include <gts/base_sequence.hpp>

#include <stdexcept>

namespace gts { namespace dsmcc { namespace biop {

namespace file_message_detail {

template <typename BaseIterator>
struct service_context_list_internal_sequence : base_sequence<BaseIterator>
{
  service_context_list_internal_sequence(BaseIterator first, BaseIterator last)
    : base_sequence<BaseIterator>(first, last) {}
};

}

namespace file_message_iterators {

template <typename BaseIterator>
struct object_info_iterator;

template <typename BaseIterator>
struct file_message_body_iterator;

template <typename BaseIterator>
struct end_iterator;

}

// Defined in ISO IEC 13818-6:1998 page 310
template <typename BaseIterator>
struct file_message
{
  typedef file_message_iterators::object_info_iterator<BaseIterator> object_info_iterator;
  typedef object_info_iterator begin_iterator;
  typedef file_message_iterators::file_message_body_iterator<BaseIterator> file_message_body_iterator;
  typedef biop::service_context_list_iterator
    <BaseIterator
     , file_message_detail::service_context_list_internal_sequence<BaseIterator>
     , file_message_body_iterator
     , file_message_body<BaseIterator> >
    service_context_list_iterator;
  typedef file_message_iterators::end_iterator<BaseIterator> end_iterator;

  file_message(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;

  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

namespace file_message_iterators {

template <typename BaseIterator>
struct object_info_iterator
  : biop::object_info_iterator<BaseIterator, file_message<BaseIterator>
                               , typename file_message<BaseIterator>::service_context_list_iterator
                               , file_message_detail::service_context_list_internal_sequence<BaseIterator>
                               , boost::mpl::size_t<0u> >
{
  typedef biop::object_info_iterator<BaseIterator, file_message<BaseIterator>
                                     , typename file_message<BaseIterator>::service_context_list_iterator
                                     , file_message_detail::service_context_list_internal_sequence<BaseIterator>
                                     , boost::mpl::size_t<0u> > base_type;
  typedef boost::mpl::int_<64> bits_content_size;
  typedef file_object_info<BaseIterator> deref_type;
  
  object_info_iterator(typename base_type::sequence_type const& sequence)
    : base_type(sequence)
    , content_size_iterator(this->last)
  {
    if(boost::distance(this->object_info) >= bits_content_size::value/CHAR_BIT)
    {
      content_size_iterator = boost::begin(this->object_info);
      this->object_info = boost::make_iterator_range
        (algorithm::position<bits_content_size::value>(content_size_iterator)
         , boost::end(this->object_info));
    }
  }

  deref_type operator*() const
  {
    if(content_size_iterator == this->last)
      throw std::runtime_error("Couldn't read content size from objectinfo");
    boost::uint_t<64u>::least content_size = algorithm::parse_data
      <boost::uint_t<64u>::least, 0u, bits_content_size::value>
      (content_size_iterator);
    return deref_type(content_size, this->object_info);
  }

  BaseIterator content_size_iterator;
};

template <typename BaseIterator>
struct file_message_body_iterator
{
  typedef file_message_body<BaseIterator> sequence_type;
  typedef BaseIterator base_type;
  typedef sequence_type deref_type;
  typedef end_iterator<BaseIterator> next_type;
  
  file_message_body_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  deref_type operator*() const
  {
    return sequence;
  }
  next_type operator++() const
  {
    return next_type(sequence.end().base());
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef BaseIterator base_type;

  end_iterator(BaseIterator current) : current(current) {}

  base_type base() const { return current; }

  BaseIterator current;
};

}

template <typename BaseIterator>
typename file_message<BaseIterator>::begin_iterator file_message<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename file_message<BaseIterator>::end_iterator file_message<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
