///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_BIND_HPP
#define GTS_DSMCC_BIOP_BIND_HPP

#include <gts/dsmcc/biop/iop_ior.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct bind_name
{
  bind_name(boost::iterator_range<BaseIterator> id
            , boost::iterator_range<BaseIterator> kind)
    : id(id), kind(kind)
  {
  }
  
  boost::iterator_range<BaseIterator> id, kind;
};

template <typename BaseIterator>
struct bind
{
  typedef biop::bind_name<BaseIterator> bind_name;
  bind(std::vector<bind_name> names)
    : names(names)
    , binding_type(1u) {}
  bind()
    : binding_type(1u) {}

  std::vector<bind_name> names;
  boost::uint_t<8>::least binding_type;
  biop::iop_ior<BaseIterator> ior;
};

} } }

#endif
