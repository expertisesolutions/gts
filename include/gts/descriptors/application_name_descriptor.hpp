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

#ifndef GTS_DESCRIPTORS_APPLICATION_NAME_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_APPLICATION_NAME_DESCRIPTOR_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/descriptors/tagged_descriptor.hpp>
#include <gts/static_offset_size_iterator.hpp>
#include <gts/adaptation_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace descriptors {

namespace application_name_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct names_iterator;

template <typename BaseIterator>
struct end_iterator;

}

namespace application_name_descriptor_detail {

namespace name_iterators {

template <typename BaseIterator>
struct iso_639_language_code_iterator;

template <typename BaseIterator>
struct application_name_length_iterator;

template <typename BaseIterator>
struct application_name_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct name
{
  typedef name_iterators::iso_639_language_code_iterator<BaseIterator>
    iso_639_language_code_iterator;
  typedef iso_639_language_code_iterator begin_iterator;
  typedef name_iterators::application_name_length_iterator<BaseIterator>
    application_name_length_iterator;

  typedef name_iterators::application_name_iterator<BaseIterator>
    application_name_iterator;

  typedef name_iterators::end_iterator<BaseIterator> end_iterator;

  name() {}
  name(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}
  
  typedef BaseIterator base_iterator;
  
  base_iterator base_begin() const { return first; }
  base_iterator base_end() const { return last; }

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

namespace name_iterators {

struct size_comparable {};
struct offset_comparable {};

template <typename BaseIterator>
struct iso_639_language_code_iterator : static_offset_size_iterator
<iso_639_language_code_iterator<BaseIterator>, BaseIterator
 , name<BaseIterator>, boost::mpl::size_t<0u>
 , boost::mpl::size_t<24u>, unsigned int
 , application_name_length_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef name<BaseIterator> sequence_type;

  iso_639_language_code_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct application_name_length_iterator : static_offset_size_iterator
<application_name_length_iterator<BaseIterator>, BaseIterator
 , name<BaseIterator>, boost::mpl::size_t<24u>
 , boost::mpl::size_t<8u>, unsigned int
 , application_name_iterator<BaseIterator> >
  , size_comparable, offset_comparable
{
  typedef name<BaseIterator> sequence_type;

  application_name_length_iterator(sequence_type const& sequence)
  : sequence(sequence) {}
  
  sequence_type sequence;
};

template <typename BaseIterator>
struct application_name_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<32u> bits_offset;
  typedef name<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;

  application_name_iterator(sequence_type const& sequence)
  : sequence(sequence) {}

  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); }
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename name<BaseIterator>::begin_iterator name<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
struct name_iterator
  : boost::iterator_facade<name_iterator<BaseIterator>
                           , name<BaseIterator>
                           , boost::forward_traversal_tag
                           , name<BaseIterator> >
{
  typedef name_iterator<BaseIterator> self_type;

  name_iterator(BaseIterator first, BaseIterator end)
    : end(end), name_(first, end)
  {
    name_.last = last();
  }

  BaseIterator last() const
  {
    typedef boost::mpl::size_t<24u> size_bits_offset;
    typedef boost::mpl::size_t<8u> size_bits_size;
    BaseIterator last;
    unsigned int max_distance = std::distance(name_.base_begin(), end);
    if(max_distance < (size_bits_offset::value+size_bits_size::value)/CHAR_BIT)
      last = end;
    else
    {
      last = name_.base_begin();
      std::advance(last, (std::min<unsigned int>)
                   (algorithm::parse_data<unsigned int
                    , size_bits_offset::value, size_bits_size::value>
                    (name_.base_begin())
                    + (size_bits_offset::value+size_bits_size::value)/CHAR_BIT
                    , max_distance));
    }
    assert(last <= end);
    return last;
  }

  void increment()
  {
    name_.first = name_.base_end();
    name_.last = last();
  }
  bool equal(self_type const& other) const
  {
    assert(name_.base_begin() != other.name_.base_begin()
           || name_.base_end() == other.name_.base_end());
    return name_.base_begin() == other.name_.base_begin();
  }
  name<BaseIterator> dereference() const
  {
    return name_;
  }

  BaseIterator end;
  name<BaseIterator> name_;
};

}

// Defined in ETSI 102 809 v1.1.1 (2010-01) page 38
template <typename BaseIterator>
struct application_name_descriptor : tagged_descriptor<BaseIterator>
{
  typedef tagged_descriptor<BaseIterator> base_type;
  typedef application_name_descriptor_iterators::tag_iterator<BaseIterator> tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef application_name_descriptor_iterators::names_iterator<BaseIterator> names_iterator;
  typedef application_name_descriptor_iterators::end_iterator<BaseIterator> end_iterator;
  
  begin_iterator begin() const;
  end_iterator end() const;

  application_name_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  application_name_descriptor(base_type base)
    : base_type(base) {}
};

namespace application_name_descriptor_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , application_name_descriptor<BaseIterator>
                        , typename application_name_descriptor<BaseIterator>
                          ::names_iterator
                        >
  , offset_comparable, size_comparable
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef application_name_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , application_name_descriptor<BaseIterator>
                              , typename application_name_descriptor<BaseIterator>
                                ::names_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct names_iterator
{
  typedef gts::iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<16u> bits_offset;
  typedef application_name_descriptor<BaseIterator> sequence_type;
  typedef application_name_descriptor_detail
    ::name_iterator<BaseIterator> name_iterator;
  typedef boost::iterator_range<name_iterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef BaseIterator base_type;

  names_iterator(sequence_type const& sequence
                 , typename tagged_descriptor<BaseIterator>::data_iterator)
  : sequence(sequence) {}
  base_type base() const
  {
    return algorithm::position<bits_offset::value>
      (sequence.base_begin());
  }
  deref_type operator*() const
  {
    return deref_type(name_iterator(base(), sequence.base_end())
                      , name_iterator(sequence.base_end(), sequence.base_end()));
  }
  next_type operator++() const;

  sequence_type sequence;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename application_name_descriptor<BaseIterator>::begin_iterator
application_name_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}

} }

#endif
