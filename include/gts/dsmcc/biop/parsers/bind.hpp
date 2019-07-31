///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_PARSERS_BIND_HPP
#define GTS_DSMCC_BIOP_PARSERS_BIND_HPP

#include <gts/dsmcc/biop/parsers/prefixed_string.hpp>
#include <gts/dsmcc/biop/parsers/iop_ior.hpp>
#include <gts/dsmcc/biop/bind.hpp>

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <typename BaseIterator>
biop::bind<BaseIterator> bind(BaseIterator& first, BaseIterator last)
{
  biop::bind<BaseIterator> r;

  typedef boost::mpl::int_<8u> names_count_bits_size;
  typedef boost::mpl::int_<8u> id_length_bits_size;
  typedef boost::mpl::int_<8u> kind_length_bits_size;
  typedef boost::mpl::int_<8u> binding_type_bits_size;
  typedef boost::mpl::int_<16u> object_info_size_bits_size;
  boost::uint_t<8u>::least names = algorithm::parse_data
    <boost::uint_t<8u>::least, 0u, names_count_bits_size::value>(first);
  if(std::distance(first, last) >= names_count_bits_size::value/CHAR_BIT)
  {
    first = algorithm::position<names_count_bits_size::value>(first);
    while(names-- && first != last)
    {
      boost::iterator_range<BaseIterator> id
        = parsers::prefixed_string<id_length_bits_size::value>
        (first, last);
      boost::iterator_range<BaseIterator> kind
        = parsers::prefixed_string<kind_length_bits_size::value>
        (first, last);

      r.names.push_back(biop::bind_name<BaseIterator>(id, kind));
    }
  }
  if(std::distance(first, last) >= binding_type_bits_size::value/CHAR_BIT)
  {
    r.binding_type = algorithm::parse_data
      <boost::uint_t<binding_type_bits_size::value>::least, 0u, binding_type_bits_size::value>
      (first);
    first = algorithm::position<binding_type_bits_size::value>(first);
    r.ior = parsers::iop_ior(first, last);

    boost::iterator_range<BaseIterator> object_info = parsers::prefixed_string
      <object_info_size_bits_size::value>(first, last);
  }
  else
    first = last;

  return r;
}

} } } }

#endif
