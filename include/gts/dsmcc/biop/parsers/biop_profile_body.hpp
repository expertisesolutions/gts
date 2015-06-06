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

#ifndef GTS_DSMCC_BIOP_PARSERS_BIOP_PROFILE_BODY_HPP
#define GTS_DSMCC_BIOP_PARSERS_BIOP_PROFILE_BODY_HPP

#include <gts/dsmcc/biop/parsers/prefixed_string.hpp>
#include <gts/dsmcc/biop/biop_profile.hpp>

namespace gts { namespace dsmcc { namespace biop { namespace parsers {

template <typename BaseIterator>
void parse_object_location(BaseIterator& first, BaseIterator last
                           , biop::object_location<BaseIterator>& object_location)
{
  int const carousel_id_bits_size = 32;
  typedef boost::uint_t<carousel_id_bits_size>::least carousel_id_type;
  int const module_id_bits_size = 16;
  typedef boost::uint_t<module_id_bits_size>::least module_id_type;
  int const version_major_bits_size = 8, version_minor_bits_size = 8;
  typedef boost::uint_t<version_major_bits_size>::least version_major_type;
  typedef boost::uint_t<version_minor_bits_size>::least version_minor_type;
  int const object_key_length_bits_size = 8;
  if(std::distance(first, last) >= 
     (carousel_id_bits_size + module_id_bits_size + version_major_bits_size
      + version_minor_bits_size)/CHAR_BIT)
  {
    carousel_id_type carousel_id = algorithm::parse_data
      <carousel_id_type, 0u, carousel_id_bits_size>(first);
    first = algorithm::position<carousel_id_bits_size>(first);
  //std::cout << "Carousel id: " << carousel_id << std::endl;
    module_id_type module_id = algorithm::parse_data
      <module_id_type, 0u, module_id_bits_size>(first);
    first = algorithm::position<module_id_bits_size>(first);
  // std::cout << "module id: " << module_id << std::endl;
    version_major_type version_major = algorithm::parse_data
      <version_major_type, 0u, version_major_bits_size>(first);
    first = algorithm::position<version_major_bits_size>(first);
    version_minor_type version_minor = algorithm::parse_data
      <version_minor_type, 0u, version_minor_bits_size>(first);
    first = algorithm::position<version_minor_bits_size>(first);
  // std::cout << "Version major " << (int)version_major << std::endl;
  // std::cout << "Version minor " << (int)version_minor << std::endl;
    if(version_major == 1 && version_minor == 0)
    {
      boost::iterator_range<BaseIterator> object_key
        = parsers::prefixed_string<object_key_length_bits_size>(first, last);
    
      object_location.carousel_id = carousel_id;
      object_location.module_id = module_id;
      object_location.object_key = object_key;
      // std::cout << "position: " << (void*)first << std::endl;
    }
    first = last;
  }
}

template <typename BaseIterator>
void parse_conn_binder(BaseIterator& first, BaseIterator last
                       , biop::conn_binder& conn_binder)
{
  int const taps_count_bits_size = 8;
  typedef boost::uint_t<taps_count_bits_size>::least taps_count_type;
  int const id_bits_size = 16;
  typedef boost::uint_t<id_bits_size>::least id_type;
  int const use_bits_size = 16;
  typedef boost::uint_t<use_bits_size>::least use_type;
  int const assoc_tag_bits_size = 16;
  typedef boost::uint_t<assoc_tag_bits_size>::least assoc_tag_type;
  int const selector_length_bits_size = 8;
  typedef boost::uint_t<selector_length_bits_size>::least selector_length_type;
  int const selector_type_bits_size = 16;
  typedef boost::uint_t<selector_type_bits_size>::least selector_type_type;
  int const transaction_id_bits_size = 32;
  typedef boost::uint_t<transaction_id_bits_size>::least transaction_id_type;
  int const timeout_bits_size = 32;
  typedef boost::uint_t<timeout_bits_size>::least timeout_type;

  if(std::distance(first, last) >= 
     (taps_count_bits_size + id_bits_size + use_bits_size
      + assoc_tag_bits_size + selector_length_bits_size
      + selector_type_bits_size + transaction_id_bits_size
      + timeout_bits_size)/CHAR_BIT)
  {
    taps_count_type taps_count = algorithm::parse_data
      <taps_count_type, 0u, taps_count_bits_size>(first);
    id_type id = algorithm::parse_data
      <id_type, taps_count_bits_size, id_bits_size>(first);
    use_type use = algorithm::parse_data
      <use_type, taps_count_bits_size+id_bits_size, use_bits_size>(first);
    assoc_tag_type assoc_tag = algorithm::parse_data
      <assoc_tag_type, taps_count_bits_size+id_bits_size+use_bits_size
       , assoc_tag_bits_size>(first);
    selector_length_type selector_length = algorithm::parse_data
      <selector_length_type, taps_count_bits_size+id_bits_size+use_bits_size
       +assoc_tag_bits_size
       , selector_length_bits_size>(first);
    if(selector_length == 10)
    {
      selector_type_type selector_type = algorithm::parse_data
        <selector_type_type, taps_count_bits_size+id_bits_size+use_bits_size
         +assoc_tag_bits_size+selector_length_bits_size
         , selector_type_bits_size>(first);
      if(selector_type == 1)
      {
        transaction_id_type transaction_id = algorithm::parse_data
          <transaction_id_type, taps_count_bits_size+id_bits_size+use_bits_size
           +assoc_tag_bits_size+selector_length_bits_size+selector_type_bits_size
           , transaction_id_bits_size>(first);
        timeout_type timeout = algorithm::parse_data
          <timeout_type, taps_count_bits_size+id_bits_size+use_bits_size
           +assoc_tag_bits_size+selector_length_bits_size+selector_type_bits_size
           +transaction_id_bits_size 
           , timeout_bits_size>(first);
        conn_binder.delivery_para_use_tap.id = id;
        conn_binder.delivery_para_use_tap.use = use;
        conn_binder.delivery_para_use_tap.assoc_tag = assoc_tag;
        conn_binder.delivery_para_use_tap.selector_length = selector_length;
        conn_binder.delivery_para_use_tap.selector_type = selector_type;
        conn_binder.delivery_para_use_tap.transaction_id = transaction_id;
        conn_binder.delivery_para_use_tap.timeout = timeout;
      }
    }
  }
}

template <typename BaseIterator>
biop_profile<BaseIterator> biop_profile_body(BaseIterator& first, BaseIterator last)
{
  biop_profile<BaseIterator> r;
  int const profile_data_byte_order_bits_size = 8;
  typedef boost::uint_t<profile_data_byte_order_bits_size>::least profile_data_byte_order_type;
  int const lite_components_count_bits_size = 8;
  typedef boost::uint_t<lite_components_count_bits_size>::least lite_components_count_type;
  int const component_id_tag_bits_size = 32;
  typedef boost::uint_t<component_id_tag_bits_size>::least component_id_tag_type;
  int const component_data_length_bits_size = 8;

  if(std::distance(first, last) >= profile_data_byte_order_bits_size/CHAR_BIT)
  {
    profile_data_byte_order_type byte_order = algorithm::parse_data
      <profile_data_byte_order_type, 0u, profile_data_byte_order_bits_size>(first);
    first = algorithm::position<profile_data_byte_order_bits_size>(first);
    if(byte_order == 0)
    {
      if(std::distance(first, last) >= lite_components_count_bits_size/CHAR_BIT)
      {
        lite_components_count_type lite_components = algorithm::parse_data
          <lite_components_count_type, 0u, lite_components_count_bits_size>(first);
        first = algorithm::position<lite_components_count_bits_size>(first);
        
        while(lite_components--
              && std::distance(first, last) >= component_id_tag_bits_size/CHAR_BIT)
        {
          component_id_tag_type component_id_tag = algorithm::parse_data
            <component_id_tag_type, 0u, component_id_tag_bits_size>(first);
          first = algorithm::position<component_id_tag_bits_size>(first);

          boost::iterator_range<BaseIterator> lite_component
            = parsers::prefixed_string<component_data_length_bits_size>(first, last);

          switch(component_id_tag)
          {
          case 0x49534F50:
          {
            BaseIterator first_lite = boost::begin(lite_component)
              , last_lite = boost::end(lite_component);
            parse_object_location(first_lite, last_lite, r.object_location);
          }
          break;
          case 0x49534f40:
          {
            BaseIterator first_lite = boost::begin(lite_component)
              , last_lite = boost::end(lite_component);
            parse_conn_binder(first_lite, last_lite, r.conn_binder);
            break;
          }
          default:
            break;
          }
        }        
      }
    }
  }
  return r;
}

} } } }

#endif
