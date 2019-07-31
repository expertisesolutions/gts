///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ITERATORS_FORWARD_ITERATOR_CONCEPT_HPP
#define GTS_ITERATORS_FORWARD_ITERATOR_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/concept/convertible_to.hpp>
#include <gts/iterators/stationary_iterator_concept.hpp>
#include <gts/iterators/next.hpp>
#include <gts/iterators/deref.hpp>
#include <gts/iterators/base.hpp>
#include <gts/iterators/iterator_tag.hpp>

namespace gts { namespace iterators {

template <typename X>
struct ForwardIteratorConcept : StationaryIteratorConcept<X>
{
  typedef typename iterators::result_of::next<X>::type next_type;
  typedef typename iterators::result_of::deref<X>::type deref_type;
  typedef typename iterators::result_of::base<X>::type base_type;
  typedef typename iterators::iterator_tag<X>::type iterator_tag;
  BOOST_MPL_ASSERT((boost::is_convertible<iterator_tag, iterators::forward_iterator_tag>));
  typedef typename iterators::iterator_tag<next_type>::type next_iterator_tag;
  typedef typename boost::is_convertible<next_iterator_tag, iterators::forward_iterator_tag>::type
    is_next_forward;

  template <typename T>
  void check_next_iterator(iterators::stationary_iterator_tag)
  {
    BOOST_CONCEPT_ASSERT((StationaryIteratorConcept<T>));
  }

  template <typename T>
  void check_next_iterator(iterators::forward_iterator_tag)
  {
    BOOST_CONCEPT_ASSERT((ForwardIteratorConcept<T>));
  }

  BOOST_CONCEPT_USAGE(ForwardIteratorConcept)
  {
    gts::concept::convertible_to<next_type>(gts::iterators::next(i));
    gts::concept::convertible_to<deref_type>(gts::iterators::deref(i));
    gts::concept::convertible_to<base_type>(gts::iterators::base(i));
    i == next_iterator;
    next_iterator == i;
  }

  X i;
  next_type next_iterator;
};

} }

#endif
