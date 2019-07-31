///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_CONCEPT_CONVERTIBLE_TO_HPP
#define GTS_CONCEPT_CONVERTIBLE_TO_HPP

#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/assert.hpp>

namespace gts { namespace concept {

template <typename To, typename From>
void convertible_to(From const&)
{
  BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
}

} }

#endif
