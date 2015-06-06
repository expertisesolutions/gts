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

#ifndef GTS_SECTIONS_APPLICATION_INFORMATION_SECTION_HPP
#define GTS_SECTIONS_APPLICATION_INFORMATION_SECTION_HPP

#include <gts/descriptors/tagged_descriptor.hpp>

#include <boost/integer.hpp>

namespace gts { namespace sections {

template <typename BaseIterator>
struct application_descriptor_iterator
  : boost::iterator_facade<application_descriptor_iterator<BaseIterator>
                           , gts::descriptors::tagged_descriptor<BaseIterator>
                           , boost::forward_traversal_tag
                           , gts::descriptors::tagged_descriptor<BaseIterator> >
{
  application_descriptor_iterator()
    : current(), last() {}
  application_descriptor_iterator(BaseIterator current, BaseIterator last)
    : current(current), last(last) {}

  void increment()
  {
    boost::uint_t<8u>::exact size = algorithm::parse_data
      <boost::uint_t<8u>::exact, 8u, 8u>(current);
    current = boost::next(current, size+2);
  }
  gts::descriptors::tagged_descriptor<BaseIterator> dereference() const
  {
    boost::uint_t<8u>::exact size = algorithm::parse_data
      <boost::uint_t<8u>::exact, 8u, 8u>(current);
    return gts::descriptors::tagged_descriptor<BaseIterator>(current, boost::next(current, size+2));
  }
  bool equal(application_descriptor_iterator<BaseIterator> const& other) const
  {
    return current == other.current;
  }

  BaseIterator current, last;
};

namespace application_information_iterators {

template <typename BaseIterator>
struct organization_identifier_iterator;

template <typename BaseIterator>
struct application_identifier_iterator;

template <typename BaseIterator>
struct application_control_code_iterator;

template <typename BaseIterator>
struct application_descriptors_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct application_information
{
  typedef application_information_iterators::organization_identifier_iterator<BaseIterator>
    organization_identifier_iterator;
  typedef organization_identifier_iterator begin_iterator;
  typedef application_information_iterators::application_identifier_iterator<BaseIterator>
    application_identifier_iterator;
  typedef application_information_iterators::application_control_code_iterator<BaseIterator>
    application_control_code_iterator;
  typedef application_information_iterators::application_descriptors_iterator<BaseIterator>
    application_descriptors_iterator;
  typedef application_information_iterators::end_iterator<BaseIterator> end_iterator;

  application_information(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  begin_iterator begin() const;
  end_iterator end() const;

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  BaseIterator first, last;
};

namespace application_information_iterators {
  
template <typename BaseIterator>
struct organization_identifier_iterator : static_offset_size_iterator
  <organization_identifier_iterator<BaseIterator>, BaseIterator, application_information<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<32u>, boost::uint_t<32u>::exact
   , application_identifier_iterator<BaseIterator> >
{
  typedef application_information<BaseIterator> sequence_type;

  organization_identifier_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct application_identifier_iterator : static_offset_size_iterator
  <application_identifier_iterator<BaseIterator>, BaseIterator, application_information<BaseIterator>
   , boost::mpl::size_t<32u>, boost::mpl::size_t<16u>, boost::uint_t<16u>::exact
   , application_control_code_iterator<BaseIterator> >
{
  typedef application_information<BaseIterator> sequence_type;

  application_identifier_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct application_control_code_iterator : static_offset_size_iterator
  <application_control_code_iterator<BaseIterator>, BaseIterator, application_information<BaseIterator>
   , boost::mpl::size_t<48u>, boost::mpl::size_t<8u>, unsigned int
   , application_descriptors_iterator<BaseIterator> >
{
  typedef application_information<BaseIterator> sequence_type;

  application_control_code_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct application_descriptors_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef application_information<BaseIterator> sequence_type;
  typedef boost::iterator_range<application_descriptor_iterator<BaseIterator> > deref_type;
  typedef end_iterator<BaseIterator> next_type;

  application_descriptors_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  deref_type operator*() const
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 60u, 12u>(sequence.base_begin());
    BaseIterator first = algorithm::position<72u>(sequence.base_begin());
    BaseIterator last = boost::next(first
                                    , (std::min<unsigned int>)
                                    (std::distance(first, sequence.base_begin())
                                     , size));
    typedef application_descriptor_iterator<BaseIterator> iterator_type;
    return deref_type(iterator_type(first, last), iterator_type(last, last));
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename application_information<BaseIterator>::begin_iterator
application_information<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename application_information<BaseIterator>::end_iterator
application_information<BaseIterator>::end() const
{
  return end_iterator(*this);
}

namespace application_information_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_identifier_iterator;

template <typename BaseIterator>
struct section_length_iterator;

template <typename BaseIterator>
struct application_type_iterator;

template <typename BaseIterator>
struct version_number_iterator;

template <typename BaseIterator>
struct current_next_indicator_iterator;

template <typename BaseIterator>
struct section_number_iterator;

template <typename BaseIterator>
struct last_section_number_iterator;

template <typename BaseIterator>
struct descriptors_iterator;

template <typename BaseIterator>
struct applications_iterator;

template <typename BaseIterator>
struct crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct application_application_iterator
  : boost::iterator_facade<application_application_iterator<BaseIterator>
                           , application_information<BaseIterator>
                           , boost::forward_traversal_tag
                           , application_information<BaseIterator> >
{
  application_application_iterator()
    : current(), last() {}
  application_application_iterator(BaseIterator current, BaseIterator last)
    : current(current), last(last) {}

  void increment()
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 60u, 12u>(current);
    std::advance(current, 72u/CHAR_BIT + size);
  }
  application_information<BaseIterator> dereference() const
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 60u, 12u>(current);
    BaseIterator next = boost::next(current, 72u/CHAR_BIT + size);
    return application_information<BaseIterator>(current, next);
  }
  bool equal(application_application_iterator<BaseIterator> const& other) const
  {
    return current == other.current;
  }
  
  BaseIterator current, last;
};

template <typename BaseIterator>
struct application_information_section
{
  typedef application_information_section_iterators::table_id_iterator<BaseIterator> table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef application_information_section_iterators::section_syntax_identifier_iterator<BaseIterator> 
    section_syntax_identifier_iterator;
  typedef application_information_section_iterators::section_length_iterator<BaseIterator> section_length_iterator;
  typedef application_information_section_iterators::application_type_iterator<BaseIterator>
    application_type_iterator;
  typedef application_information_section_iterators::version_number_iterator<BaseIterator> version_number_iterator;
  typedef application_information_section_iterators::current_next_indicator_iterator<BaseIterator>
    current_next_indicator_iterator;
  typedef application_information_section_iterators::section_number_iterator<BaseIterator> section_number_iterator;
  typedef application_information_section_iterators::last_section_number_iterator<BaseIterator>
    last_section_number_iterator;
  typedef application_information_section_iterators::descriptors_iterator<BaseIterator> descriptors_iterator;
  typedef application_information_section_iterators::applications_iterator<BaseIterator> applications_iterator;
  typedef application_information_section_iterators::end_iterator<BaseIterator> end_iterator;

  application_information_section(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  begin_iterator begin() const;
  end_iterator end() const;

  typedef BaseIterator base_iterator;
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  BaseIterator first, last;
};

namespace application_information_section_iterators {

struct offset_comparable {};

template <typename BaseIterator>
struct table_id_iterator : static_offset_size_iterator
  <table_id_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<0u>, boost::mpl::size_t<8u>, boost::uint_t<8u>::exact
   , section_syntax_identifier_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  table_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct section_syntax_identifier_iterator : static_offset_size_iterator
  <section_syntax_identifier_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<8u>, boost::mpl::size_t<1u>, bool
   , section_length_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  section_syntax_identifier_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_length_iterator : static_offset_size_iterator
  <section_length_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<12u>, boost::mpl::size_t<12u>, unsigned int
   , application_type_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  section_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct application_type_iterator : static_offset_size_iterator
  <application_type_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<24u>, boost::mpl::size_t<16u>, unsigned int
   , version_number_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  application_type_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct version_number_iterator : static_offset_size_iterator
  <version_number_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<42u>, boost::mpl::size_t<5u>, unsigned int
   , current_next_indicator_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  version_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct current_next_indicator_iterator : static_offset_size_iterator
  <current_next_indicator_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<47u>, boost::mpl::size_t<1u>, bool
   , section_number_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  current_next_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct section_number_iterator : static_offset_size_iterator
  <section_number_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<48u>, boost::mpl::size_t<8u>, unsigned int
   , last_section_number_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  section_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct last_section_number_iterator : static_offset_size_iterator
  <last_section_number_iterator<BaseIterator>, BaseIterator, application_information_section<BaseIterator>
   , boost::mpl::size_t<56u>, boost::mpl::size_t<8u>, unsigned int
   , descriptors_iterator<BaseIterator> >
{
  typedef application_information_section<BaseIterator> sequence_type;

  last_section_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct descriptors_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef application_information_section<BaseIterator> sequence_type;
  typedef boost::iterator_range<application_descriptor_iterator<BaseIterator> > deref_type;
  typedef applications_iterator<BaseIterator> next_type;

  descriptors_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {
  }

  deref_type operator*() const
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 68u, 12u>(sequence.base_begin());
    BaseIterator first = algorithm::position<80u>(sequence.base_begin());
    BaseIterator last = boost::next(first
                                    , (std::min<unsigned int>)
                                    (std::distance(first, sequence.base_begin())
                                     , size));
    typedef application_descriptor_iterator<BaseIterator> iterator_type;
    return deref_type(iterator_type(first, last), iterator_type(last, last));
  }
  next_type operator++() const
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 68u, 12u>(sequence.base_begin());
    BaseIterator first = algorithm::position<80u>(sequence.base_begin());
    BaseIterator last = boost::next(first
                                    , (std::min<unsigned int>)
                                    (std::distance(first, sequence.base_begin())
                                     , size));
    return next_type(sequence, last);
  }

  sequence_type sequence;
};

template <typename BaseIterator>
struct applications_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef application_information_section<BaseIterator> sequence_type;
  typedef boost::iterator_range<application_application_iterator<BaseIterator> > deref_type;
  typedef applications_iterator<BaseIterator> next_type;

  applications_iterator(sequence_type const& sequence, BaseIterator current)
    : sequence(sequence), current(current) {}

  deref_type operator*() const
  {
    unsigned int size = algorithm::parse_data
      <unsigned int, 4u, 12u>(current);
    BaseIterator first = algorithm::position<16u>(current);
    BaseIterator last = boost::next(first
                                    , (std::min<unsigned int>)
                                    (std::distance(first, sequence.base_begin())
                                     , size));
    typedef application_application_iterator<BaseIterator> iterator_type;
    return deref_type(iterator_type(first, last), iterator_type(last, last));
  }
  next_type operator++() const;

  sequence_type sequence;
  BaseIterator current;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename application_information_section<BaseIterator>::begin_iterator
application_information_section<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename application_information_section<BaseIterator>::end_iterator
application_information_section<BaseIterator>::end () const
{
  return end_iterator(*this);
}

} }

#endif
