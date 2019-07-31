///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_END_ITERATOR_CONCEPT_HPP
#define GTS_ITERATORS_END_ITERATOR_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/iterators/iterator_tag.hpp>
#include <gts/iterators/base.hpp>

namespace gts { namespace iterators {

template <typename X>
struct StationaryIteratorConcept : boost::EqualityComparable<X>
  , boost::CopyConstructible<X>
{
  typedef typename iterators::iterator_tag<X>::type iterator_tag;
  typedef typename iterators::result_of::base<X>::type base_type;
  BOOST_MPL_ASSERT((boost::is_convertible<iterator_tag, stationary_iterator_tag>));
};

} }

#endif
