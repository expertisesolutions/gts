///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONCEPT_ADAPTATION_FIELD_HPP
#define GTS_CONCEPT_ADAPTATION_FIELD_HPP

#include <gts/concept/convertible_to.hpp>

#include <boost/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace gts { namespace concept {

template <typename T>
struct adaptation_field_traits
{
  typedef boost::mpl::false_ is_adaptation_field;
};

template <typename X>
struct AdaptationField
{
  typedef adaptation_field_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_adaptation_field::value, ==, true);
  typedef typename traits::boolean_type boolean_type;
  typedef typename traits::pcr_type pcr_type;
  typedef typename traits::splice_countdown_type splice_countdown_type;

  BOOST_CONCEPT_USAGE(AdaptationField)
  {
    convertible_to<boolean_type>(traits::discontinuity_indicator(field));
    convertible_to<boolean_type>(traits::random_access_indicator(field));
    convertible_to<boolean_type>(traits::es_priority_indicator(field));
    convertible_to<boolean_type>(traits::pcr_exists(field));
    convertible_to<boolean_type>(traits::opcr_exists(field));
    convertible_to<boolean_type>(traits::splicing_point_exists(field));
    convertible_to<boolean_type>(traits::transport_private_data_exists(field));
    convertible_to<boolean_type>(traits::adaptation_field_extension_exists(field));
    convertible_to<pcr_type>(traits::pcr(field));
    convertible_to<pcr_type>(traits::opcr(field));
    convertible_to<splice_countdown_type>(traits::splice_countdown(field));
  }

  X field;
};

} }

#endif
