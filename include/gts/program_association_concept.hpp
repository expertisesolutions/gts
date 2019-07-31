///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAM_ASSOCIATIONS_CONCEPT_HPP
#define GTS_PROGRAM_ASSOCIATIONS_CONCEPT_HPP

#include <boost/concept_check.hpp>

#include <gts/concept/convertible_to.hpp>
#include <gts/sequences/sequence_concept.hpp>

namespace gts {

template <typename X>
struct ProgramAssociationConcept : boost::CopyConstructible<X>
  , boost::EqualityComparable<X>, gts::sequences::SequenceConcept<X>
{
  typedef typename X::program_number_iterator program_number_iterator;
  typedef typename X::pid_iterator pid_iterator;
  typedef typename X::end_iterator end_iterator;

  BOOST_CONCEPT_USAGE(ProgramAssociationConcept)
  {
    concept::convertible_to<program_number_iterator>(sequences::begin(program_association));
    concept::convertible_to<end_iterator>(sequences::end(program_association));
    concept::convertible_to<pid_iterator>(iterators::next(program_number));
    concept::convertible_to<end_iterator>(iterators::next(pid));
  }

  X program_association;
  program_number_iterator program_number;
  pid_iterator pid;
  end_iterator end;
};

}

#endif
