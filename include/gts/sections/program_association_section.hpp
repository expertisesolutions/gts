///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SECTIONS_PROGRAM_ASSOCIATION_SECTION_HPP
#define GTS_SECTIONS_PROGRAM_ASSOCIATION_SECTION_HPP

#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/algorithm/static_parsing.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/size_t.hpp>

#include <algorithm>
#include <cassert>

namespace gts { namespace sections {

namespace program_association_section_iterators {

template <typename BaseIterator>
struct table_id_iterator;

template <typename BaseIterator>
struct section_syntax_indicator_iterator;

template <typename BaseIterator>
struct section_length_iterator;

template <typename BaseIterator>
struct transport_stream_id_iterator;

template <typename BaseIterator>
struct version_number_iterator;

template <typename BaseIterator>
struct current_next_indicator_iterator;

template <typename BaseIterator>
struct section_number_iterator;

template <typename BaseIterator>
struct last_section_number_iterator;

template <typename BaseIterator>
struct program_associations_iterator;

template <typename BaseIterator>
struct crc32_iterator;

template <typename BaseIterator>
struct end_iterator;

}

namespace program_association_iterators {

template <typename BaseIterator>
struct program_number_iterator;

template <typename BaseIterator>
struct pid_iterator;

template <typename BaseIterator>
struct end_iterator;

}

template <typename BaseIterator>
struct program_associations_range
{
  program_associations_range(BaseIterator first, BaseIterator last)
    : first(first), last(last)
  {
    assert((std::distance(first, last) % 4) == 0);
  }

  struct program_association
  {
    unsigned int program_number;
    unsigned int pid;
  };

  struct iterator : boost::iterator_facade<iterator
                                           , program_association
                                           , boost::forward_traversal_tag
                                           , program_association>
  {
    iterator () {}
    iterator(BaseIterator base_it)
      : base_it(base_it) {}

    void increment()
    {
      std::advance(base_it, 32u/CHAR_BIT);
    }
    bool equal(iterator const& other) const { return base_it == other.base_it; }
    program_association dereference() const
    {
      unsigned int program_number = algorithm::parse_data
        <unsigned int, 0u, 16u>(base_it);
      unsigned int pid = algorithm::parse_data
        <unsigned int, 16u + 3u, 16u - 3u>(base_it);
      program_association p = {program_number, pid};
      return p;
    }

    BaseIterator base_it;
  };
  typedef iterator const_iterator;

  iterator begin() const
  {
    return iterator(first);
  }
  iterator end() const
  {
    return iterator(last);
  }

  BaseIterator first, last;
};

template <typename BaseIterator>
struct program_association_section
{
  program_association_section(BaseIterator first, BaseIterator last)
    : first(first), last(last) {}

  typedef program_association_section_iterators::table_id_iterator<BaseIterator> table_id_iterator;
  typedef table_id_iterator begin_iterator;
  typedef program_association_section_iterators::section_syntax_indicator_iterator<BaseIterator> section_syntax_indicator_iterator;
  typedef program_association_section_iterators::section_length_iterator<BaseIterator> section_length_iterator;
  typedef program_association_section_iterators::transport_stream_id_iterator<BaseIterator> transport_stream_id_iterator;
  typedef program_association_section_iterators::version_number_iterator<BaseIterator> version_number_iterator;
  typedef program_association_section_iterators::current_next_indicator_iterator<BaseIterator> current_next_indicator_iterator;
  typedef program_association_section_iterators::section_number_iterator<BaseIterator> section_number_iterator;
  typedef program_association_section_iterators::last_section_number_iterator<BaseIterator> last_section_number_iterator;
  typedef program_association_section_iterators::program_associations_iterator<BaseIterator> program_associations_iterator;
  typedef program_association_section_iterators::crc32_iterator<BaseIterator> crc32_iterator;
  typedef program_association_section_iterators::end_iterator<BaseIterator> end_iterator;

  begin_iterator begin() const;
  end_iterator end() const;

  BaseIterator first, last;
};

template <typename BaseIterator>
bool operator==(program_association_section<BaseIterator> const& lhs, program_association_section<BaseIterator> const& rhs)
{
  return (lhs.first == rhs.first && lhs.last == rhs.last)
    || (std::distance(lhs.first, lhs.last) == std::distance(rhs.first, rhs.last)
        && std::equal(lhs.first, lhs.last, rhs.first));
}

template <typename BaseIterator>
bool operator!=(program_association_section<BaseIterator> const& lhs, program_association_section<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

namespace program_association_section_iterators {

struct offset_comparable {};
struct size_comparable {};

template <typename BaseIterator>
struct table_id_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<0u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef std::size_t deref_type;

  table_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef section_syntax_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_syntax_indicator_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<8u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  section_syntax_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef section_length_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_length_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<12u> bits_offset;
  typedef boost::mpl::size_t<12u> bits_size;
  typedef std::size_t deref_type;

  section_length_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef transport_stream_id_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct transport_stream_id_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<24u> bits_offset;
  typedef boost::mpl::size_t<16u> bits_size;
  typedef std::size_t deref_type;

  transport_stream_id_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef version_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct version_number_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<42u> bits_offset;
  typedef boost::mpl::size_t<5u> bits_size;
  typedef std::size_t deref_type;

  version_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef current_next_indicator_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct current_next_indicator_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<47u> bits_offset;
  typedef boost::mpl::size_t<1u> bits_size;
  typedef bool deref_type;

  current_next_indicator_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct section_number_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<48u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef bool deref_type;

  section_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef last_section_number_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct last_section_number_iterator : offset_comparable, size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<56u> bits_offset;
  typedef boost::mpl::size_t<8u> bits_size;
  typedef bool deref_type;

  last_section_number_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    return algorithm::parse_data<deref_type, bits_offset::value, bits_size::value>(sequence.first);
  }
  typedef program_associations_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct program_associations_iterator : offset_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<64u> bits_offset;
  typedef program_associations_range<BaseIterator> deref_type;

  program_associations_iterator(sequence_type const& sequence)
    : sequence(sequence) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return algorithm::position<bits_offset::value>(sequence.first); }
  deref_type operator*() const
  {
    BOOST_MPL_ASSERT_RELATION((bits_offset::value % CHAR_BIT), ==, 0u);
    BaseIterator first = boost::next(sequence.first, bits_offset::value/CHAR_BIT);
    std::size_t chars = std::distance(first, sequence.last);
    if(chars >= 4)
    {
      BaseIterator last = boost::next(first, chars - 4);
      return deref_type(first, last);
    }
    else
      return deref_type(first, first);
  }
  typedef crc32_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    BOOST_MPL_ASSERT_RELATION((bits_offset::value % CHAR_BIT), ==, 0u);
    BaseIterator first = boost::next(sequence.first, bits_offset::value/CHAR_BIT);
    std::size_t chars = std::distance(first, sequence.last);
    if(chars >= 4)
    {
      BaseIterator last = boost::next(first, chars - 4);
      return next_type(sequence, last);
    }
    else
      return next_type(sequence, sequence.last);
  }

  sequence_type sequence;  
};

template <typename BaseIterator>
struct crc32_iterator : size_comparable
{
  typedef program_association_section<BaseIterator> sequence_type;
  typedef boost::mpl::size_t<32u> bits_size;
  typedef std::size_t deref_type;

  crc32_iterator(sequence_type const& sequence, BaseIterator crc32_start)
    : sequence(sequence), crc32_start(crc32_start) {}

  typedef iterators::forward_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const { return crc32_start; }
  deref_type operator*() const
  {
    deref_type r = 0;
    assert(std::distance(crc32_start, sequence.last) == sizeof(r));
    BOOST_MPL_ASSERT_RELATION(sizeof(r), ==, (bits_size::value/CHAR_BIT) + ((bits_size::value%CHAR_BIT==0)?0:1));
#if 1
    std::reverse_copy(crc32_start
                      , boost::next(crc32_start, sizeof(r))
                      , static_cast<unsigned char*>(static_cast<void*>(&r)));
#else
    std::copy(crc32_start
              , boost::next(crc32_start, sizeof(r))
              , static_cast<unsigned char*>(static_cast<void*>(&r)));
#endif
    return r;
  }
  typedef end_iterator<BaseIterator> next_type;
  next_type operator++() const
  {
    return next_type(sequence, boost::next(crc32_start, bits_size::value/CHAR_BIT));
  }

  sequence_type sequence;  
  BaseIterator crc32_start;
};

template <typename BaseIterator>
struct end_iterator
{
  typedef program_association_section<BaseIterator> sequence_type;

  end_iterator(sequence_type const& sequence, BaseIterator end)
    : sequence(sequence) {}

  typedef iterators::stationary_iterator_tag iterator_tag;
  typedef BaseIterator base_type;
  base_type base() const;

  sequence_type const& sequence;
  BaseIterator end;
};

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator> const& lhs, end_iterator<BaseIterator> const& rhs)
{
  return true;
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> const& lhs, end_iterator<BaseIterator> const& rhs)
{
  return !(lhs == rhs);
}

template <typename BaseIterator, typename Iterator>
typename boost::enable_if
<boost::is_convertible<Iterator, offset_comparable>, bool>::type
operator==(end_iterator<BaseIterator> lhs, Iterator rhs)
{
  return std::distance(lhs.sequence.first, lhs.end)
    <= Iterator::bits_offset::value / CHAR_BIT;
}

template <typename BaseIterator, typename Iterator>
typename boost::enable_if
<boost::is_convertible<Iterator, offset_comparable>, bool>::type
operator==(Iterator lhs, end_iterator<BaseIterator> rhs)
{
  std::size_t distance = std::distance(rhs.sequence.first, rhs.end);
  return distance <= Iterator::bits_offset::value / CHAR_BIT;
}

template <typename BaseIterator, typename Iterator>
typename boost::enable_if
<boost::is_convertible<Iterator, offset_comparable>, bool>::type
operator!=(end_iterator<BaseIterator> lhs, Iterator rhs)
{
  return !(lhs == rhs);
}

template <typename BaseIterator, typename Iterator>
typename boost::enable_if
<boost::is_convertible<Iterator, offset_comparable>, bool>::type
operator!=(Iterator lhs, end_iterator<BaseIterator> rhs)
{
  return !(lhs == rhs);
}

template <typename BaseIterator>
bool operator==(end_iterator<BaseIterator> lhs, crc32_iterator<BaseIterator> rhs)
{
  return lhs.end <= rhs.crc32_start;
}

template <typename BaseIterator>
bool operator==(crc32_iterator<BaseIterator> lhs, end_iterator<BaseIterator> rhs)
{
  return rhs.end <= lhs.crc32_start;
}

template <typename BaseIterator>
bool operator!=(crc32_iterator<BaseIterator> lhs, end_iterator<BaseIterator> rhs)
{
  return !(lhs == rhs);
}

template <typename BaseIterator>
bool operator!=(end_iterator<BaseIterator> lhs, crc32_iterator<BaseIterator> rhs)
{
  return !(lhs == rhs);
}

template <typename Iterator1, typename Iterator2>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<Iterator1, offset_comparable>
                  , boost::is_convertible<Iterator2, offset_comparable> >
 , bool>::type
operator==(Iterator1 lhs, Iterator2 rhs)
{
  return Iterator1::bits_offset::value == Iterator2::bits_offset::value;
}

template <typename Iterator1, typename Iterator2>
typename boost::enable_if
<boost::mpl::and_<boost::is_convertible<Iterator1, offset_comparable>
                  , boost::is_convertible<Iterator2, offset_comparable> >
 , bool>::type
operator!=(Iterator1 lhs, Iterator2 rhs)
{
  return !(lhs == rhs);
}

}

template <typename BaseIterator>
typename program_association_section<BaseIterator>::begin_iterator program_association_section<BaseIterator>::begin () const
{
  return begin_iterator(*this);
}

template <typename BaseIterator>
typename program_association_section<BaseIterator>::end_iterator program_association_section<BaseIterator>::end () const
{
  return end_iterator(*this, last);
}

} }

#endif
