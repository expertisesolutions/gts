///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DESCRIPTORS_GROUP_INFO_HPP
#define GTS_DSMCC_DESCRIPTORS_GROUP_INFO_HPP

#include <gts/dsmcc/descriptors/compatibility_descriptor.hpp>

#include <boost/integer.hpp>

namespace gts { namespace dsmcc { namespace descriptors {

template <typename BaseIterator>
struct group_info
{
  boost::uint_t<32u>::least group_id, group_size;
  compatibility_descriptor<BaseIterator> group_compatibility;
  boost::iterator_range<BaseIterator> group_info;
  boost::iterator_range<BaseIterator> private_data;
};

} } }

#endif
