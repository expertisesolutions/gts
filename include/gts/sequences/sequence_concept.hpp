///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SEQUENCES_SEQUENCE_CONCEPT_HPP
#define GTS_SEQUENCES_SEQUENCE_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/concept/convertible_to.hpp>
#include <gts/iterators/stationary_iterator_concept.hpp>
#include <gts/iterators/forward_iterator_concept.hpp>
#include <gts/iterators/bidirectional_iterator_concept.hpp>
#include <gts/sequences/begin.hpp>
#include <gts/sequences/end.hpp>

namespace gts { namespace sequences {

template <typename X>
struct SequenceConcept
{
  typedef typename sequences::result_of::begin<X>::type begin_type;
  typedef typename sequences::result_of::end<X>::type end_type;
  BOOST_CONCEPT_ASSERT((iterators::StationaryIteratorConcept<begin_type>));
  BOOST_CONCEPT_ASSERT((iterators::StationaryIteratorConcept<end_type>));

  template <typename T>
  void check_iterator(iterators::stationary_iterator_tag)
  {
    BOOST_CONCEPT_ASSERT((iterators::StationaryIteratorConcept<T>));
  }

  template <typename T>
  void check_iterator(iterators::forward_iterator_tag)
  {
    BOOST_CONCEPT_ASSERT((iterators::ForwardIteratorConcept<T>));
  }

  template <typename T>
  void check_iterator(iterators::bidirectional_iterator_tag)
  {
    BOOST_CONCEPT_ASSERT((iterators::BidirectionalIteratorConcept<T>));
  }

  BOOST_CONCEPT_USAGE(SequenceConcept)
  {
    gts::concept::convertible_to<begin_type>(gts::sequences::begin(s));
    gts::concept::convertible_to<end_type>(gts::sequences::end(s));
    check_iterator<begin_type>(typename iterators::iterator_tag<begin_type>::type());
    check_iterator<end_type>(typename iterators::iterator_tag<end_type>::type());
  }

  X s;
};

} }

#endif
