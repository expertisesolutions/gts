///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONCEPT_RANDOM_ACCESS_SEQUENCE_HPP
#define GTS_CONCEPT_RANDOM_ACCESS_SEQUENCE_HPP

#include <gts/concept/convertible_to.hpp>
#include <gts/begin.hpp>
#include <gts/end.hpp>

#include <boost/concept_check.hpp>

namespace gts { namespace concept {

template <typename X>
struct RandomAccessSequence
{
  typedef gts::result_of::begin<X>::type begin_iterator;
  typedef gts::result_of::end<X>::type end_iterator;

  BOOST_CONCEPT_USAGE(RandomAccessSequence)
  {
    convertible_to<begin_iterator>(gts::begin(i));
    convertible_to<end_iterator>(gts::end(i));
  }

  X i;
};

} }

#endif
