///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_IOP_IOR_HPP
#define GTS_DSMCC_BIOP_IOP_IOR_HPP

#include <gts/dsmcc/biop/biop_profile.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct iop_ior
{
  iop_ior() {}
  iop_ior(boost::iterator_range<BaseIterator> type_id)
    : type_id(type_id) {}
  
  boost::iterator_range<BaseIterator> type_id;
  std::vector<biop_profile<BaseIterator> > biop_profiles;
};

template <typename BaseIterator>
bool operator==(iop_ior<BaseIterator> const& lhs, iop_ior<BaseIterator> const& rhs)
{
  return lhs.type_id == rhs.type_id && lhs.biop_profiles == rhs.biop_profiles;
}

template <typename BaseIterator>
bool operator<(iop_ior<BaseIterator> const& lhs, iop_ior<BaseIterator> const& rhs)
{
  return (lhs.type_id == rhs.type_id && lhs.biop_profiles < rhs.biop_profiles)
    || lhs.type_id < rhs.type_id;
}

} } }

#endif
