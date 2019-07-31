///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_PARSERS_IOP_IOR_HPP
#define GTS_DSMCC_BIOP_PARSERS_IOP_IOR_HPP

#include <gts/dsmcc/biop/iop_ior.hpp>
#include <gts/dsmcc/biop/parsers/prefixed_string.hpp>
#include <gts/dsmcc/biop/parsers/biop_profile_body.hpp>

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <typename BaseIterator>
biop::iop_ior<BaseIterator> iop_ior(BaseIterator& first, BaseIterator last)
{
  typedef boost::mpl::int_<32> type_id_size_bits_size;
  typedef boost::mpl::int_<32> tagged_profiles_count_bits_size;
  typedef boost::mpl::int_<32> tagged_profile_id_tag_bits_size;
  typedef boost::mpl::int_<32> tagged_profile_data_size_bits_size;

  assert(first <= last);

  boost::iterator_range<BaseIterator> type_id
    = prefixed_string<type_id_size_bits_size::value>(first, last);
  std::size_t type_id_size = boost::distance(type_id);
  std::size_t alignment = type_id_size%4;
  std::size_t max_size = std::distance(first, last);
  if(max_size >= alignment)
    std::advance(first, alignment);
  else first = last;

  biop::iop_ior<BaseIterator> ior(type_id);
  if(std::distance(first, last) >= tagged_profiles_count_bits_size::value/CHAR_BIT)
  {
    boost::uint_t<tagged_profiles_count_bits_size::value>::least tagged_profiles
      = algorithm::parse_data<boost::uint_t<tagged_profiles_count_bits_size::value>::least
                              , 0u, tagged_profiles_count_bits_size::value>(first);
    first = algorithm::position<tagged_profiles_count_bits_size::value>(first);

    while(tagged_profiles-- && first != last)
    {
      if(std::distance(first, last) >= tagged_profile_id_tag_bits_size::value/CHAR_BIT)
      {
        boost::uint_t<tagged_profile_id_tag_bits_size::value>::least profile_id_tag
          = algorithm::parse_data
          <boost::uint_t<tagged_profile_id_tag_bits_size::value>::least, 0u
           , tagged_profile_id_tag_bits_size::value>(first);
        first = algorithm::position<tagged_profile_id_tag_bits_size::value>(first);
        if(profile_id_tag == 0x49534F06)
        {
          boost::iterator_range<BaseIterator> profile_data = parsers::prefixed_string
            <tagged_profile_data_size_bits_size::value>(first, last);
          BaseIterator profile_first = boost::begin(profile_data);
          biop_profile<BaseIterator> biop_profile = biop_profile_body(profile_first, boost::end(profile_data));
          ior.biop_profiles.push_back(biop_profile);
        }
      //   else if(profile_id_tag == 0x49534f40)
      //   {
      //     std::cout << "DSM::ConnBinder" << std::endl;
      //   }
        else
        {
        }
      }
      else
        first = last;
    }
  }  
  
  return ior;
}

} } } }

#endif
