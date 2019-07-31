///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_BIOP_PROFILE_HPP
#define GTS_DSMCC_BIOP_BIOP_PROFILE_HPP

#include <gts/dsmcc/biop/object_location.hpp>
#include <gts/dsmcc/biop/conn_binder.hpp>

#include <boost/variant.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct biop_profile
{
  typedef boost::variant<biop::object_location<BaseIterator>
                         , biop::conn_binder> lite_component_variant;
  biop::object_location<BaseIterator> object_location;
  biop::conn_binder conn_binder;
  std::vector<lite_component_variant> lite_components;
};

template <typename BaseIterator>
bool operator==(biop_profile<BaseIterator> const& lhs, biop_profile<BaseIterator> const& rhs)
{
  return lhs.object_location == rhs.object_location
    && lhs.conn_binder == rhs.conn_binder;
}

template <typename BaseIterator>
bool operator<(biop_profile<BaseIterator> const& lhs, biop_profile<BaseIterator> const& rhs)
{
  return (lhs.object_location == rhs.object_location
          && lhs.conn_binder == rhs.conn_binder)
    || lhs.conn_binder < rhs.conn_binder;
}

} } }

#endif
