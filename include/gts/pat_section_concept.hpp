///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PAT_SECTION_CONCEPT_HPP
#define GTS_PAT_SECTION_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/range/concepts.hpp>

#include <gts/concept/convertible_to.hpp>
#include <gts/sequences/sequence_concept.hpp>
#include <gts/program_association_concept.hpp>

namespace gts {

template <typename X>
struct PatSectionConcept : boost::CopyConstructible<X>
  , boost::EqualityComparable<X>, gts::sequences::SequenceConcept<X>
{
  typedef typename X::table_id_iterator table_id_iterator;
  typedef typename X::section_syntax_indicator_iterator section_syntax_indicator_iterator;
  typedef typename X::section_length_iterator section_length_iterator;
  typedef typename X::transport_stream_id_iterator transport_stream_id_iterator;
  typedef typename X::version_number_iterator version_number_iterator;
  typedef typename X::current_next_indicator_iterator current_next_indicator_iterator;
  typedef typename X::section_number_iterator section_number_iterator;
  typedef typename X::last_section_number_iterator last_section_number_iterator;
  typedef typename X::program_associations_iterator program_associations_iterator;
  typedef typename X::crc32_iterator crc32_iterator;
  typedef typename X::end_iterator end_iterator;

  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept
                        <typename gts::iterators::result_of::deref<program_associations_iterator>::type>));
  BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept
                        <typename boost::range_iterator
                         <typename gts::iterators::result_of::deref<program_associations_iterator>::type
                          >::type>));

  BOOST_CONCEPT_USAGE(PatSectionConcept)
  {
    concept::convertible_to<table_id_iterator>(sequences::begin(section));
    concept::convertible_to<end_iterator>(sequences::end(section));
    concept::convertible_to<section_syntax_indicator_iterator>(iterators::next(table_id));
    concept::convertible_to<section_length_iterator>(iterators::next(section_syntax_indicator));
    concept::convertible_to<transport_stream_id_iterator>(iterators::next(section_length));
    concept::convertible_to<version_number_iterator>(iterators::next(transport_stream_id));
    concept::convertible_to<current_next_indicator_iterator>(iterators::next(version_number));
    concept::convertible_to<section_number_iterator>(iterators::next(current_next_indicator));
    concept::convertible_to<last_section_number_iterator>(iterators::next(section_number));
    concept::convertible_to<program_associations_iterator>(iterators::next(last_section_number));
    concept::convertible_to<crc32_iterator>(iterators::next(program_associations));
    concept::convertible_to<end_iterator>(iterators::next(crc32));
  }

  X section;
  table_id_iterator table_id;
  section_syntax_indicator_iterator section_syntax_indicator;
  section_length_iterator section_length;
  transport_stream_id_iterator transport_stream_id;
  version_number_iterator version_number;
  current_next_indicator_iterator current_next_indicator;
  section_number_iterator section_number;
  last_section_number_iterator last_section_number;
  program_associations_iterator program_associations;
  crc32_iterator crc32;
  end_iterator end;
};

}

#endif
