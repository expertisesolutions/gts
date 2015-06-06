/* (c) Copyright 2011-2014 Felipe Magno de Almeida
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
