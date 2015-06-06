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
