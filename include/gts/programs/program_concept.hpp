///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAM_PROGRAM_CONCEPT_HPP
#define GTS_PROGRAM_PROGRAM_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/programs/es_buffer_concept.hpp>
#include <gts/programs/es_buffer.hpp>
#include <gts/programs/has_es_buffer.hpp>
#include <gts/concept/convertible_to.hpp>

namespace gts { namespace programs {

template <typename X>
struct ProgramConcept : boost::EqualityComparable<X>
  , boost::CopyConstructible<X>
{
  typedef typename programs::result_of::es_buffer<X>::type es_buffer_type;

  BOOST_CONCEPT_ASSERT((ESBufferConcept<es_buffer_type>));

  BOOST_CONCEPT_USAGE(ProgramConcept)
  {
    programs::has_es_buffer(const_program, pid);
    concept::convertible_to<es_buffer_type>(programs::es_buffer(program, pid));
  }

#ifdef _MSC_VER
  ProgramConcept();
#endif

  std::size_t pid;
  X program;
  X const const_program;
};

} }

#endif
