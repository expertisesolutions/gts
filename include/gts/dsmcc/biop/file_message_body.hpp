///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_FILE_MESSAGE_BODY_HPP
#define GTS_DSMCC_BIOP_FILE_MESSAGE_BODY_HPP

namespace gts { namespace dsmcc { namespace biop {

namespace file_message_body_iterators {

template <typename BaseIterator>
struct message_body_length_iterator;

template <typename BaseIterator>
struct content_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct file_message_body
{
  typedef file_message_body_iterators::message_body_length_iterator<BaseIterator>
    message_body_length_iterator;
  typedef message_body_length_iterator begin_iterator;
  typedef file_message_body_iterators::content_iterator<BaseIterator> content_iterator;
  typedef file_message_body_iterators::end_iterator<BaseIterator> end_iterator;

  file_message_body(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;
  
  BaseIterator first, last;
};

namespace file_message_body_iterators {

template <typename BaseIterator>
struct message_body_length_iterator : static_offset_size_iterator
<message_body_length_iterator<BaseIterator>, BaseIterator, file_message_body<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
 , content_iterator<BaseIterator> >
{
  typedef static_offset_size_iterator
  <message_body_length_iterator<BaseIterator>, BaseIterator, file_message_body<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
   , content_iterator<BaseIterator> > base_type;
  typedef file_message_body<BaseIterator> sequence_type;
  typedef typename base_type::next_type next_type;

  message_body_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}
  next_type operator++() const
  {
    return next_type(sequence, **this);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct content_iterator : static_offset_size_iterator
<content_iterator<BaseIterator>, BaseIterator, file_message_body<BaseIterator>
 , boost::mpl::size_t<32u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
 , end_iterator<BaseIterator> >
{
  typedef static_offset_size_iterator
  <content_iterator<BaseIterator>, BaseIterator, file_message_body<BaseIterator>
   , boost::mpl::size_t<32u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::least
   , end_iterator<BaseIterator> > base_type;
  typedef typename base_type::sequence_type sequence_type;
  typedef typename base_type::next_type next_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef typename base_type::bits_size bits_size;

  content_iterator(sequence_type const& sequence, std::size_t message_body_length)
    : sequence(sequence), message_body_length(message_body_length)
    , content_first(algorithm::position<bits_size::value>(this->base()))
    , content_last(sequence.base_end())
  {
    typename base_type::deref_type size = base_type::operator*();
    if(std::distance(content_first, content_last) > size)
      content_last = boost::next(content_first, size);
    
  }

  deref_type operator*() const
  {
    return deref_type(content_first, content_last);
  }
  next_type operator++() const
  {
    return next_type(sequence, content_last);
  }

  sequence_type sequence;
  std::size_t message_body_length;
  BaseIterator content_first, content_last;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef file_message_body<BaseIterator> sequence_type;
  end_iterator(sequence_type const& sequence, BaseIterator base)
    : sequence(sequence), base_(base) {}

  BaseIterator base() const { return base_; }

  sequence_type sequence;
  BaseIterator base_;
};

}

template <typename BaseIterator>
typename file_message_body<BaseIterator>::begin_iterator file_message_body<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename file_message_body<BaseIterator>::end_iterator file_message_body<BaseIterator>::end() const
{
  return end_iterator(*this);
}

} } }

#endif
