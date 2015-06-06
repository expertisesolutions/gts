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

#ifndef GTS_SECTIONS_PMT_PROGRAM_MAP_REPETITION_HPP
#define GTS_SECTIONS_PMT_PROGRAM_MAP_REPETITION_HPP

#include <gts/descriptor_private_range.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>
#include <gts/static_offset_size_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace sections { namespace pmt {

namespace program_map_repetition_iterators {

template <typename BaseIterator>
struct stream_type_iterator;

template <typename BaseIterator>
struct elementary_pid_iterator;

template <typename BaseIterator>
struct es_info_length_iterator;

template <typename BaseIterator>
struct descriptor_repetition_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct program_map_repetition
{
  program_map_repetition(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef program_map_repetition_iterators::stream_type_iterator<BaseIterator> stream_type_iterator;
  typedef stream_type_iterator begin_iterator;
  typedef program_map_repetition_iterators::elementary_pid_iterator<BaseIterator> elementary_pid_iterator;
  typedef program_map_repetition_iterators::es_info_length_iterator<BaseIterator> es_info_length_iterator;
  typedef program_map_repetition_iterators::descriptor_repetition_iterator<BaseIterator>
    descriptor_repetition_iterator;
  typedef program_map_repetition_iterators::end_iterator<BaseIterator> end_iterator;

  typedef BaseIterator base_iterator;
  base_iterator base_begin () const { return first; }
  base_iterator base_end () const { return last; }

  begin_iterator begin () const;
  end_iterator end () const;

  base_iterator first, last;
};

namespace program_map_repetition_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct stream_type_iterator : static_offset_size_iterator
<stream_type_iterator<BaseIterator>, BaseIterator, program_map_repetition<BaseIterator>
 , boost::mpl::size_t<0u>, boost::mpl::size_t<8u>, unsigned int, elementary_pid_iterator<BaseIterator> >
{
  typedef program_map_repetition<BaseIterator> sequence_type;

  stream_type_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct elementary_pid_iterator : static_offset_size_iterator
<elementary_pid_iterator<BaseIterator>, BaseIterator, program_map_repetition<BaseIterator>
 , boost::mpl::size_t<11u>, boost::mpl::size_t<13u>, unsigned int, es_info_length_iterator<BaseIterator> >
{
  typedef program_map_repetition<BaseIterator> sequence_type;

  elementary_pid_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct es_info_length_iterator : static_offset_size_iterator
<es_info_length_iterator<BaseIterator>, BaseIterator, program_map_repetition<BaseIterator>
 , boost::mpl::size_t<28u>, boost::mpl::size_t<12u>, unsigned int, descriptor_repetition_iterator<BaseIterator> >
{
  typedef program_map_repetition<BaseIterator> sequence_type;

  es_info_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  sequence_type sequence;
};

template <typename BaseIterator>
struct descriptor_repetition_iterator : offset_comparable
{
  typedef program_map_repetition<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<40u> bits_offset;
  typedef descriptor_private_range<BaseIterator> deref_type;
  typedef BaseIterator base_type;
  typedef end_iterator<BaseIterator> next_type;

  descriptor_repetition_iterator(sequence_type const& sequence)
    : sequence(sequence)
  {}

  typedef iterators::forward_iterator_tag iterator_tag;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    es_info_length_iterator<BaseIterator>
      length = gts::iterators::next<2>(sequence.begin ());
    return deref_type(base ()
                      , boost::next(base (), *length));
  }
  next_type operator++() const;
  // {
  //   program_info_length_iterator<BaseIterator>
  //     length = gts::iterators::next<6>(sequence.begin ());
  //   return next_type(sequence, boost::next(base (), *length));
  // }

  sequence_type sequence;
};

}

template <typename BaseIterator>
typename program_map_repetition<BaseIterator>::begin_iterator
program_map_repetition<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

} } }

#endif
