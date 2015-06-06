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

#ifndef GTS_DESCRIPTORS_GINGA_APPLICATION_LOCATION_DESCRIPTOR_HPP
#define GTS_DESCRIPTORS_GINGA_APPLICATION_LOCATION_DESCRIPTOR_HPP

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

namespace ginga_application_location_descriptor_iterators {

template <typename BaseIterator>
struct tag_iterator;

template <typename BaseIterator>
struct base_directory_iterator;

template <typename BaseIterator>
struct classpath_extension_iterator;

template <typename BaseIterator>
struct initial_class_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct ginga_application_location_descriptor : tagged_descriptor<BaseIterator>
{
  typedef tagged_descriptor<BaseIterator> base_type;
  typedef ginga_application_location_descriptor_iterators::tag_iterator<BaseIterator>
    tag_iterator;
  typedef tag_iterator begin_iterator;
  typedef ginga_application_location_descriptor_iterators::base_directory_iterator<BaseIterator>
    base_directory_iterator;
  typedef ginga_application_location_descriptor_iterators::classpath_extension_iterator<BaseIterator>
  classpath_extension_iterator;
  typedef ginga_application_location_descriptor_iterators::initial_class_iterator<BaseIterator>
    initial_class_iterator;
  typedef ginga_application_location_descriptor_iterators::end_iterator<BaseIterator>
    end_iterator;
  
  ginga_application_location_descriptor(BaseIterator first, BaseIterator last)
    : base_type(first, last) {}
  ginga_application_location_descriptor(base_type base)
    : base_type(base) {}

  typedef BaseIterator base_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

namespace ginga_application_location_descriptor_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct tag_iterator
  : adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                        , ginga_application_location_descriptor<BaseIterator>
                        , typename ginga_application_location_descriptor<BaseIterator>
                          ::base_directory_iterator
                        >
  , offset_comparable, size_comparable
{
  typedef typename tagged_descriptor<BaseIterator>::tag_iterator base_iterator;
  typedef ginga_application_location_descriptor<BaseIterator> sequence_type;
  typedef adaptation_iterator<typename tagged_descriptor<BaseIterator>::tag_iterator
                              , ginga_application_location_descriptor<BaseIterator>
                              , typename ginga_application_location_descriptor<BaseIterator>
                                ::base_directory_iterator
                              > adaptation_base;

  tag_iterator(sequence_type const& sequence)
  : adaptation_base(sequence, base_iterator(sequence)) {}
};

template <typename BaseIterator>
struct base_directory_iterator
{
  typedef BaseIterator base_type;
  typedef ginga_application_location_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef classpath_extension_iterator<BaseIterator> next_type;
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef boost::mpl::size_t<16u> size_bits_offset;
  typedef boost::mpl::size_t<8u> size_bits_size;
  
  base_directory_iterator(sequence_type const& sequence
                          , typename tagged_descriptor<BaseIterator>::data_iterator)
    : sequence(sequence)
  {
    base_directory_size = algorithm::parse_data<unsigned int, size_bits_offset::value
                                                , size_bits_size::value>(sequence.base_begin());
    std::size_t max_size = std::distance(sequence.base_begin(), sequence.base_end());
    if(max_size < base_directory_size)
      base_directory_size = max_size;
  }
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.base_begin()); }
  deref_type operator*() const
  {
    BaseIterator first = base(), last = base();
    std::advance(last, base_directory_size);
    return deref_type(first, last);
  }
  next_type operator++() const
  {
    return next_type(sequence, boost::end(**this));
  }
  
  sequence_type sequence;
  unsigned int base_directory_size;
};

template <typename BaseIterator>
struct classpath_extension_iterator
{
  typedef BaseIterator base_type;
  typedef ginga_application_location_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef initial_class_iterator<BaseIterator> next_type;
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<0u> size_bits_offset;
  typedef boost::mpl::size_t<8u> size_bits_size;
  
  classpath_extension_iterator(sequence_type const& sequence, BaseIterator first)
    : sequence(sequence), first(first)
  {
    classpath_extension_size = algorithm::parse_data<unsigned int, size_bits_offset::value
                                                     , size_bits_size::value>(first);
    std::size_t max_size = std::distance(first, sequence.base_end());
    if(max_size < classpath_extension_size)
      classpath_extension_size = max_size;
  }
  base_type base() const { return algorithm::position<bits_offset::value>(first); }
  deref_type operator*() const
  {
    BaseIterator first = base(), last = base();
    std::advance(last, classpath_extension_size);
    return deref_type(first, last);
  }
  next_type operator++() const
  {
    return next_type(sequence, boost::end(**this));
  }
  
  unsigned int classpath_extension_size;
  sequence_type sequence;
  BaseIterator first;
};

template <typename BaseIterator>
struct initial_class_iterator
{
  typedef BaseIterator base_type;
  typedef ginga_application_location_descriptor<BaseIterator> sequence_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef end_iterator<BaseIterator> next_type;
  typedef iterators::forward_iterator_tag iterator_tag;
  typedef boost::mpl::size_t<0u> bits_offset;
  
  initial_class_iterator(sequence_type const& sequence, BaseIterator first)
    : sequence(sequence), first(first)
  {
  }
  base_type base() const { return algorithm::position<bits_offset::value>(first); }
  deref_type operator*() const
  {
    return deref_type(base(), sequence.base_end());
  }
  next_type operator++() const
  {
    return next_type(sequence, boost::end(**this));
  }
  
  sequence_type sequence;
  BaseIterator first;
};

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
typename ginga_application_location_descriptor<BaseIterator>::begin_iterator
ginga_application_location_descriptor<BaseIterator>::begin() const
{
  return begin_iterator(*this);
}


} }

#endif
