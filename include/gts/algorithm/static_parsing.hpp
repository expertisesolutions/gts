///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ALGORITHM_STATIC_PARSING_HPP
#define GTS_ALGORITHM_STATIC_PARSING_HPP

#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits/is_same.hpp>

#include <climits>
#include <algorithm>

namespace gts { namespace algorithm {

template <std::size_t offset, typename BaseIterator>
BaseIterator position(BaseIterator iterator)
{
  return boost::next(iterator, offset/CHAR_BIT);
}

namespace parse_detail {

template <typename R, std::size_t offset, std::size_t size, typename BaseIterator>
R parse_data_aux(BaseIterator iterator, boost::mpl::true_ /* one byte */
                 , boost::mpl::false_, boost::mpl::false_, boost::mpl::false_)
{
  const std::size_t left_empty_bits = offset % CHAR_BIT;
  const std::size_t valid_bits = size;
  const std::size_t right_empty_bits = CHAR_BIT - (valid_bits + left_empty_bits);
  return (iterator[offset / CHAR_BIT]
          & (((1 << valid_bits) - 1) << right_empty_bits))
    >> (right_empty_bits);
}

template <typename R, std::size_t offset, std::size_t size, typename BaseIterator>
R parse_data_aux(BaseIterator iterator, boost::mpl::true_, boost::mpl::true_ /* boolean */
                 , boost::mpl::false_, boost::mpl::false_)
{
  return (iterator[offset / CHAR_BIT] & (1 << ((CHAR_BIT-1) - (offset%CHAR_BIT)))) != 0;
}

template <typename R, std::size_t offset, std::size_t size, typename BaseIterator>
R parse_data_aux(BaseIterator iterator, boost::mpl::false_, boost::mpl::false_
                 , boost::mpl::true_ /* copy two bytes */, boost::mpl::false_)
{
  R r = 0;
  BOOST_MPL_ASSERT_RELATION(sizeof(R), >=, 2u);
#if 1
  const std::size_t first_byte = 0u;
  const std::size_t remaining = offset % CHAR_BIT;
  const std::size_t upper_valid_bits = (CHAR_BIT - remaining);
  const std::size_t down_valid_bits = size - upper_valid_bits;
  static_cast<unsigned char*>(static_cast<void*>(&r))[first_byte + 1]
    = iterator[offset / CHAR_BIT] & ((1 << upper_valid_bits)-1);
  static_cast<unsigned char*>(static_cast<void*>(&r))[first_byte + 0]
    = iterator[offset / CHAR_BIT + 1] & (((1 << down_valid_bits)-1) << (CHAR_BIT - down_valid_bits));
#else
  const std::size_t first_byte = sizeof(R) - 2u;
  const std::size_t remaining = offset % CHAR_BIT;
  const std::size_t upper_valid_bits = (CHAR_BIT - remaining);
  const std::size_t down_valid_bits = size - upper_valid_bits;
  static_cast<unsigned char*>(static_cast<void*>(&r))[first_byte + 0]
    = iterator[offset / CHAR_BIT] & ((1 << upper_valid_bits)-1);
  static_cast<unsigned char*>(static_cast<void*>(&r))[first_byte + 1]
    = iterator[offset / CHAR_BIT + 1] & (((1 << down_valid_bits)-1) << (CHAR_BIT - down_valid_bits));
#endif
  return r;
}

template <typename R, std::size_t offset, std::size_t size, typename BaseIterator>
R parse_data_aux(BaseIterator iterator, boost::mpl::false_, boost::mpl::false_
                 , boost::mpl::false_, boost::mpl::true_ /* copy > 2 bytes with offset % CHAR_BIT == 0 and size % CHAR_BIT == 0 */)
{
  R r = 0;
  BOOST_MPL_ASSERT_RELATION(sizeof(R), ==, size/CHAR_BIT);
  BaseIterator first = boost::next(iterator, offset/CHAR_BIT)
    , last = boost::next(first, size/CHAR_BIT);
  unsigned char* r_first = static_cast<unsigned char*>(static_cast<void*>(&r));
#if 1
  std::reverse_copy(first, last, r_first);
#else
  std::copy(first, last, r_first);
#endif
  return r;
}

}

template <typename R, std::size_t offset, std::size_t size, typename BaseIterator>
R parse_data(BaseIterator iterator)
{
  return parse_detail::parse_data_aux<R, offset, size>
    (iterator
     , boost::mpl::bool_<((size + (offset % CHAR_BIT)) <= (CHAR_BIT))>()
     , typename boost::mpl::and_
       <boost::is_same<R, bool>
        , boost::mpl::bool_<size == 1>
       >::type()
     , boost::mpl::bool_<(size + (offset % CHAR_BIT)) <= (CHAR_BIT*2)
                         && ((size + (offset % CHAR_BIT)) > (CHAR_BIT))>()
     , boost::mpl::bool_<(size > (CHAR_BIT*2))
                         && (offset % CHAR_BIT == 0)
                         && (size % CHAR_BIT == 0)>());
}

} }

#endif
