///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_PARSERS_PREFIXED_STRING_HPP
#define GTS_DSMCC_BIOP_PARSERS_PREFIXED_STRING_HPP

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <std::size_t SizeBits, typename BaseIterator>
boost::iterator_range<BaseIterator> prefixed_string(BaseIterator& first, BaseIterator last)
{
  std::size_t max_size = std::distance(first, last);
  if(max_size >= SizeBits/CHAR_BIT)
  {
    typename boost::uint_t<SizeBits>::least size = algorithm::parse_data
      <typename boost::uint_t<SizeBits>::least, 0u, SizeBits>(first);
    first = algorithm::position<SizeBits>(first);
    size = (std::min<std::size_t>)(max_size, size);
    BaseIterator last_string = boost::next(first, size);
    boost::iterator_range<BaseIterator> string(first, last_string);
    first = last_string;
    return string;
  }
  else
  {
    first = last;
    boost::iterator_range<BaseIterator> string(last, last);
    return string;
  }
}

} } } }

#endif
