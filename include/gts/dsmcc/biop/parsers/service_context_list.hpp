///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_PARSERS_SERVICE_CONTEXT_LIST_HPP
#define GTS_DSMCC_BIOP_PARSERS_SERVICE_CONTEXT_LIST_HPP

#include <boost/range/iterator_range.hpp>

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <typename BaseIterator>
boost::iterator_range<BaseIterator> service_context_list(BaseIterator& first, BaseIterator last)
{
  typedef boost::mpl::int_<8u> size_bits_size;
  if(std::distance(first, last) < size_bits_size::value/CHAR_BIT)
    return boost::iterator_range<BaseIterator>(first, first);
  else
  {
    boost::uint_t<16u>::least size = algorithm::parse_data
      <boost::uint_t<16u>::least, 0u, size_bits_size::value>(first);
    first = algorithm::position<size_bits_size::value>(first);
    BaseIterator range_first = first;
    std::advance(first, (std::min<int>)(std::distance(first, last), size));
    return boost::make_iterator_range(range_first, first);
  }
}

} } } }

#endif

