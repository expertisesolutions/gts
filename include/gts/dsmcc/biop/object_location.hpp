///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_OBJECT_LOCATION_HPP
#define GTS_DSMCC_BIOP_OBJECT_LOCATION_HPP

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct object_location
{
  object_location()
    : carousel_id(0u), module_id(0u) {}

  unsigned int carousel_id;
  unsigned int module_id;
  boost::iterator_range<BaseIterator> object_key;
};

template <typename BaseIterator>
bool operator==(object_location<BaseIterator> const& lhs, object_location<BaseIterator>const& rhs)
{
  return lhs.carousel_id == rhs.carousel_id && lhs.module_id == rhs.module_id
    && lhs.object_key == rhs.object_key;
}

template <typename BaseIterator>
bool operator<(object_location<BaseIterator> const& lhs, object_location<BaseIterator>const& rhs)
{
  return (lhs.carousel_id == rhs.carousel_id && lhs.module_id == rhs.module_id
          && lhs.object_key < rhs.object_key)
    || (lhs.carousel_id == rhs.carousel_id && lhs.module_id < rhs.module_id)
    || lhs.carousel_id < rhs.carousel_id;
}

} } }

#endif
