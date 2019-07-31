///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_SERVICE_CONTEXT_LIST_ITERATOR_HPP
#define GTS_DSMCC_BIOP_SERVICE_CONTEXT_LIST_ITERATOR_HPP

#include <gts/dsmcc/biop/parsers/service_context_list.hpp>

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator, typename Sequence, typename NextIterator
          , typename NextSequence, typename Offset = boost::mpl::size_t<0u> >
struct service_context_list_iterator
{
  typedef Sequence sequence_type;
  typedef NextIterator next_type;
  typedef boost::iterator_range<BaseIterator> deref_type;
  typedef BaseIterator base_type;

  service_context_list_iterator(sequence_type const& sequence)
    : sequence(sequence)
    , last(base())
    , deref(parsers::service_context_list(last, sequence.base_end()))
  {
    
  }

  deref_type operator*() const
  {
    return deref;
  }
  next_type operator++() const
  {
    return next_type(NextSequence(last, sequence.base_end()));
  }
  base_type base() const
  {
    return algorithm::position<Offset::value>(sequence.base_begin());
  }

  sequence_type sequence;
  BaseIterator last;
  deref_type deref;
};

} } }

#endif
