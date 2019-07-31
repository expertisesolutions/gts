///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SECTIONS_PROGRAM_MAP_SECTION_HPP
#define GTS_SECTIONS_PROGRAM_MAP_SECTION_HPP

#include <gts/descriptor_private_range.hpp>
#include <gts/adaptation_iterator.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/static_offset_size_iterator.hpp>
#include <gts/sections/pmt/program_map_repetition.hpp>
#include <gts/sections/private_section.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace sections {

template <typename BaseIterator>
struct program_map_range
{
  program_map_range(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {}

  struct iterator : boost::iterator_facade
  <iterator, pmt::program_map_repetition<BaseIterator>
   , boost::forward_traversal_tag, pmt::program_map_repetition<BaseIterator> >
  {
    iterator(BaseIterator item_first, BaseIterator last)
      : item_first(item_first), last(last)
    {
      set_item_last ();
    }

    void set_item_last ()
    {
      typedef pmt::program_map_repetition<BaseIterator> program_map_type;
      typedef typename program_map_type::es_info_length_iterator es_info_length_iterator;
      typedef typename program_map_type::descriptor_repetition_iterator descriptor_repetition_iterator;
      program_map_type deref(item_first, last);
      unsigned int length = *gts::iterators::next<2>(deref.begin ());
      item_last = last;
      if(std::distance(item_first, last) > length)
        item_last = boost::next(item_first, length
                                + descriptor_repetition_iterator::bits_offset::value / CHAR_BIT);
    }

    void increment ()
    {
      item_first = item_last;
      set_item_last ();
    }
    bool equal(iterator const& other) const
    {
      return item_first == other.item_first;
    }
    pmt::program_map_repetition<BaseIterator> dereference () const
    {
      return pmt::program_map_repetition<BaseIterator>(item_first, item_last);
    }

    BaseIterator item_first, item_last, last;
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

  typedef BaseIterator base_iterator;

  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  base_iterator first, last;
};

namespace program_map_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_indicator_iterator;

template <typename BaseIterator>
struct private_indicator_iterator;

template <typename BaseIterator>
struct private_section_length_iterator;

template <typename BaseIterator>
struct program_number_iterator;

template <typename BaseIterator>
struct version_number_iterator;

template <typename BaseIterator>
struct current_next_indicator_iterator;

template <typename BaseIterator>
struct section_number_iterator;

template <typename BaseIterator>
struct last_section_number_iterator;

template <typename BaseIterator>
struct pcr_pid_iterator;

template <typename BaseIterator>
struct program_info_length_iterator;

template <typename BaseIterator>
struct descriptor_repetition_iterator;

template <typename BaseIterator>
struct program_map_repetition_iterator;

template <typename BaseIterator>
struct crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct program_map_section : private_section<BaseIterator>
{
  typedef private_section<BaseIterator> base_type;
  program_map_section(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}

  typedef program_map_section_iterators::table_id_iterator<BaseIterator>
    table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef program_map_section_iterators::section_syntax_indicator_iterator<BaseIterator>
    section_syntax_indicator_iterator;
  typedef program_map_section_iterators::private_indicator_iterator<BaseIterator>
    private_indicator_iterator;
  typedef program_map_section_iterators::private_section_length_iterator<BaseIterator>
    private_section_length_iterator;
  typedef program_map_section_iterators::program_number_iterator<BaseIterator>
    program_number_iterator;
  typedef program_map_section_iterators::version_number_iterator<BaseIterator> version_number_iterator;
  typedef program_map_section_iterators::current_next_indicator_iterator<BaseIterator>
    current_next_indicator_iterator;
  typedef program_map_section_iterators::section_number_iterator<BaseIterator>
    section_number_iterator;
  typedef program_map_section_iterators::last_section_number_iterator<BaseIterator>
    last_section_number_iterator;
  typedef program_map_section_iterators::pcr_pid_iterator<BaseIterator>
    pcr_pid_iterator;
  typedef program_map_section_iterators::program_info_length_iterator<BaseIterator>
    program_info_length_iterator;
  typedef program_map_section_iterators::descriptor_repetition_iterator<BaseIterator> descriptor_repetition_iterator;
  typedef program_map_section_iterators::program_map_repetition_iterator<BaseIterator> program_map_repetition_iterator;
  typedef program_map_section_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin () const;
  end_iterator end () const;
};

namespace program_map_section_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct table_id_iterator : adaptation_iterator
<typename private_section<BaseIterator>::table_id_iterator
 , program_map_section<BaseIterator>
 , section_syntax_indicator_iterator<BaseIterator> >
{
  typedef adaptation_iterator
  <typename private_section<BaseIterator>::table_id_iterator
   , program_map_section<BaseIterator>
   , section_syntax_indicator_iterator<BaseIterator> >
  adaptation_base;
  typedef typename private_section<BaseIterator>::table_id_iterator base_iterator;
  typedef program_map_section<BaseIterator> sequence_type;
  table_id_iterator(sequence_type const& s)
  : adaptation_base(s, base_iterator(s)) {}
};

template <typename BaseIterator>
struct section_syntax_indicator_iterator : adaptation_iterator
<typename private_section<BaseIterator>::section_syntax_indicator_iterator
 , program_map_section<BaseIterator>
 , private_indicator_iterator<BaseIterator> >
{
  typedef adaptation_iterator
  <typename private_section<BaseIterator>::section_syntax_indicator_iterator
   , program_map_section<BaseIterator>
   , private_indicator_iterator<BaseIterator> >
  adaptation_base;
  typedef typename private_section<BaseIterator>::section_syntax_indicator_iterator base_iterator;
  typedef program_map_section<BaseIterator> sequence_type;
  section_syntax_indicator_iterator(sequence_type const& s
                                    , base_iterator const& n)
    : adaptation_base(s, n) {}
};

template <typename BaseIterator>
struct private_indicator_iterator : adaptation_iterator
<typename private_section<BaseIterator>::private_indicator_iterator
 , program_map_section<BaseIterator>
 , private_section_length_iterator<BaseIterator> >
{
  typedef adaptation_iterator
  <typename private_section<BaseIterator>::private_indicator_iterator
   , program_map_section<BaseIterator>
   , private_section_length_iterator<BaseIterator> >
  adaptation_base;
  typedef typename private_section<BaseIterator>::private_indicator_iterator base_iterator;
  typedef program_map_section<BaseIterator> sequence_type;
  private_indicator_iterator(sequence_type const& s
                             , base_iterator const& n)
    : adaptation_base(s, n) {}
};

template <typename BaseIterator>
struct private_section_length_iterator : adaptation_iterator
<typename private_section<BaseIterator>::private_section_length_iterator
 , program_map_section<BaseIterator>
 , program_number_iterator<BaseIterator> >
{
  typedef adaptation_iterator
  <typename private_section<BaseIterator>::private_section_length_iterator
   , program_map_section<BaseIterator>
   , program_number_iterator<BaseIterator> >
  adaptation_base;
  typedef typename private_section<BaseIterator>::private_section_length_iterator base_iterator;
  typedef program_map_section<BaseIterator> sequence_type;
  private_section_length_iterator(sequence_type const& s
                                  , base_iterator const& n)
    : adaptation_base(s, n) {}
};

template <typename BaseIterator>
struct program_number_iterator : static_offset_size_iterator
<program_number_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<24u>
 , boost::mpl::size_t<16u>, unsigned int, version_number_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  program_number_iterator(sequence_type const& sequence
                          , typename private_section<BaseIterator>::private_data_iterator const&)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct version_number_iterator : static_offset_size_iterator
<version_number_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<42u>
 , boost::mpl::size_t<5u>, unsigned int, current_next_indicator_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  version_number_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct current_next_indicator_iterator : static_offset_size_iterator
<current_next_indicator_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<47u>
 , boost::mpl::size_t<1u>, bool, section_number_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  current_next_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct section_number_iterator : static_offset_size_iterator
<section_number_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<48u>
 , boost::mpl::size_t<8u>, unsigned int, last_section_number_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  section_number_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct last_section_number_iterator : static_offset_size_iterator
<last_section_number_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<56u>
 , boost::mpl::size_t<8u>, unsigned int, pcr_pid_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  last_section_number_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct pcr_pid_iterator : static_offset_size_iterator
<pcr_pid_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<67u>
 , boost::mpl::size_t<13u>, unsigned int, program_info_length_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  pcr_pid_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct program_info_length_iterator : static_offset_size_iterator
<program_info_length_iterator<BaseIterator>
 , BaseIterator, program_map_section<BaseIterator>, boost::mpl::size_t<84u>
 , boost::mpl::size_t<12u>, unsigned int, descriptor_repetition_iterator<BaseIterator> >
{
  typedef program_map_section<BaseIterator> sequence_type;

  program_info_length_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct descriptor_repetition_iterator : offset_comparable
{
  typedef program_map_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<96u> bits_offset;
  typedef descriptor_private_range<BaseIterator> deref_type;
  typedef BaseIterator base_type;
  typedef program_map_repetition_iterator<BaseIterator> next_type;

  descriptor_repetition_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  typedef iterators::forward_iterator_tag iterator_tag;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    program_info_length_iterator<BaseIterator>
      length = gts::iterators::next<10>(sequence.begin ());
    return deref_type(base ()
                      , boost::next(base (), *length));
  }
  next_type operator++() const
  {
    program_info_length_iterator<BaseIterator>
      length = gts::iterators::next<10>(sequence.begin ());
    return next_type(sequence, boost::next(base (), *length));
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct program_map_repetition_iterator
{
  typedef program_map_section<BaseIterator> sequence_type;
  typedef program_map_range<BaseIterator> deref_type;
  typedef BaseIterator base_type;
  typedef crc32_iterator<BaseIterator> next_type;

  program_map_repetition_iterator(sequence_type const& sequence, BaseIterator descriptor_repetition_end)
    : sequence(sequence), descriptor_repetition_end(descriptor_repetition_end)
  {}

  typedef iterators::forward_iterator_tag iterator_tag;
  base_type base() const { return descriptor_repetition_end; }
  deref_type operator*() const
  {
    return deref_type(base ()
                      , boost::prior(sequence.last, next_type::bits_size::value/CHAR_BIT));
  }
  next_type operator++() const;
  // {
  //   program_info_length_iterator<BaseIterator>
  //     length = gts::iterators::next<6>(sequence.begin ());
  //   return next_type(sequence/*, boost::next(base (), *length)*/);
  // }

  sequence_type sequence;
  BaseIterator descriptor_repetition_end;
};

template <typename BaseIterator>
struct crc32_iterator : size_comparable
{
  typedef program_map_section<BaseIterator> sequence_type;
  typedef unsigned int deref_type;
  typedef BaseIterator base_type;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef end_iterator<BaseIterator> next_type;

  crc32_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  typedef iterators::forward_iterator_tag iterator_tag;
  base_type base() const;
  deref_type operator*() const;
  next_type operator++() const;

  sequence_type sequence;
};

}

template <typename BaseIterator>
typename program_map_section<BaseIterator>::begin_iterator
program_map_section<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

} }

#endif

