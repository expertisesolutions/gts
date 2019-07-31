///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_SECTION_USER_NETWORK_MESSAGE_SEQUENCE_HPP
#define GTS_DSMCC_SECTION_USER_NETWORK_MESSAGE_SEQUENCE_HPP

#include <gts/sections/private_section.hpp>
#include <gts/sections/extended_section.hpp>
#include <gts/dsmcc/user_network_message.hpp>

namespace gts { namespace dsmcc { namespace sections {

namespace user_network_message_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_indicator_iterator;

template <typename BaseIterator>
struct private_indicator_iterator;

template <typename BaseIterator>
struct dsmcc_section_length_iterator;

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
struct user_network_message_iterator;

template <typename BaseIterator>
struct checksum_or_crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct user_network_message_section
{
  typedef gts::sections::extended_section<BaseIterator> extended_section_type;
  
  typedef user_network_message_section_iterators::table_id_iterator<BaseIterator>
    table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef user_network_message_section_iterators
    ::section_syntax_indicator_iterator<BaseIterator> section_syntax_indicator_iterator;
  typedef user_network_message_section_iterators
    ::dsmcc_section_length_iterator<BaseIterator> dsmcc_section_length_iterator;
  typedef user_network_message_section_iterators
    ::private_indicator_iterator<BaseIterator> private_indicator_iterator;
  typedef user_network_message_section_iterators
    ::table_id_extension_iterator<BaseIterator> table_id_extension_iterator;
  typedef user_network_message_section_iterators
    ::version_number_iterator<BaseIterator> version_number_iterator;
  typedef user_network_message_section_iterators
    ::current_next_indicator_iterator<BaseIterator> current_next_indicator_iterator;
  typedef user_network_message_section_iterators
    ::section_number_iterator<BaseIterator> section_number_iterator;
  typedef user_network_message_section_iterators
    ::last_section_number_iterator<BaseIterator> last_section_number_iterator;
  typedef user_network_message_section_iterators
    ::user_network_message_iterator<BaseIterator> user_network_message_iterator;
  typedef user_network_message_section_iterators
    ::checksum_or_crc32_iterator<BaseIterator> checksum_or_crc32_iterator;
  typedef user_network_message_section_iterators::end_iterator<BaseIterator>
    end_iterator;

  user_network_message_section(BaseIterator first, BaseIterator last)
    : first(first), last(last), extended_section(first, last)
  {}
  user_network_message_section(extended_section_type const& extended_section)
    : first(extended_section.first), last(extended_section.last)
    , extended_section(extended_section)
  {}

  begin_iterator begin () const;
  end_iterator end () const;

  BaseIterator first, last;
  extended_section_type extended_section;
};

namespace user_network_message_section_iterators {

template <typename BaseIterator>
struct table_id_iterator : user_network_message_section<BaseIterator>
  ::extended_section_type::table_id_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::table_id_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  table_id_iterator(sequence_type const& sequence)
    : base_type(sequence.extended_section), sequence(sequence) {}

  typedef section_syntax_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct section_syntax_indicator_iterator : user_network_message_section
  <BaseIterator>::extended_section_type::section_syntax_indicator_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::section_syntax_indicator_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  section_syntax_indicator_iterator(sequence_type const& sequence
                                    , base_type iterator)
    : base_type(iterator), sequence(sequence) {}

  typedef private_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct private_indicator_iterator : user_network_message_section
  <BaseIterator>::extended_section_type::private_indicator_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::private_indicator_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  private_indicator_iterator(sequence_type const& sequence
                              , base_type iterator)
    : base_type(iterator), sequence(sequence) {}

  typedef dsmcc_section_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct dsmcc_section_length_iterator : user_network_message_section
  <BaseIterator>::extended_section_type::private_section_length_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::private_section_length_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  dsmcc_section_length_iterator(sequence_type const& sequence)
    : base_type(sequence.extended_section), sequence(sequence) {}

  typedef table_id_extension_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct table_id_extension_iterator : user_network_message_section
  <BaseIterator>::extended_section_type::table_id_extension_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::table_id_extension_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  table_id_extension_iterator(sequence_type const& sequence
                              , base_type iterator)
    : base_type(iterator), sequence(sequence)
  {}

  typedef version_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct version_number_iterator : user_network_message_section
  <BaseIterator>::extended_section_type::version_number_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::version_number_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  version_number_iterator(sequence_type const& sequence
                          , base_type iterator)
    : base_type(iterator), sequence(sequence)
  {}

  typedef current_next_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct current_next_indicator_iterator : user_network_message_section
    <BaseIterator>::extended_section_type::current_next_indicator_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::current_next_indicator_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  current_next_indicator_iterator(sequence_type const& sequence
                                  , base_type iterator)
    : base_type(iterator), sequence(sequence)
  {}

  typedef section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next (get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct section_number_iterator : user_network_message_section
    <BaseIterator>::extended_section_type::section_number_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::section_number_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  section_number_iterator(sequence_type const& sequence
                          , base_type iterator)
    : base_type(iterator), sequence(sequence)
  {}

  typedef last_section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next (get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct last_section_number_iterator : user_network_message_section
    <BaseIterator>::extended_section_type::last_section_number_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef typename extended_section_type::last_section_number_iterator base_type;

  base_type& get_base () { return *this; }
  base_type const& get_base () const { return *this; }

  last_section_number_iterator(sequence_type const& sequence
                               , base_type iterator)
    : base_type(iterator), sequence(sequence)
  {}

  typedef user_network_message_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, gts::iterators::next(get_base ()));
  }

  sequence_type const& sequence;
};

template <typename BaseIterator>
struct user_network_message_iterator
{
  typedef user_network_message_section<BaseIterator> sequence_type;
  typedef typename sequence_type::extended_section_type extended_section_type;
  typedef gts::dsmcc::user_network_message<BaseIterator> deref_type;
  typedef typename extended_section_type::private_data_iterator base_iterator;

  user_network_message_iterator(sequence_type const& sequence
                                , base_iterator base)
    : base_(base), sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return base_.base (); }
  deref_type operator*() const
  {
    typename base_iterator::deref_type r = *base_;
    return deref_type(boost::begin (r), boost::end(r));
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const;
  
  base_iterator base_;
  sequence_type const& sequence;
};

template <typename BaseIterator>
struct checksum_or_crc32_iterator;

template <typename BaseIterator>
struct end_iterator
{
  typedef user_network_message_section<BaseIterator> self_type;
  typedef typename self_type::private_section_type private_section_type;
  typedef typename private_section_type::table_id_iterator base_type;

  end_iterator(self_type const& self)
    : self(self) {}

  self_type const& self;
};

}

template <typename BaseIterator>
typename user_network_message_section<BaseIterator>::begin_iterator
user_network_message_section<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename user_network_message_section<BaseIterator>::end_iterator
user_network_message_section<BaseIterator>::end () const
{
  return end_iterator(*this);
}

} } }

#endif
