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

#ifndef GTS_TAG_SEQUENCE_ITERATOR_HPP
#define GTS_TAG_SEQUENCE_ITERATOR_HPP

// #include <gts/dereference.hpp>
// #include <gts/base.hpp>
// #include <gts/next.hpp>
// #include <gts/is_equal.hpp>

// #include <boost/mpl/size_t.hpp>
// #include <boost/mpl/equal_to.hpp>
// #include <boost/mpl/less.hpp>

// #include <boost/utility/enable_if.hpp>
// #include <boost/utility.hpp>

// #include <climits>
// #include <algorithm>

// namespace gts {

// namespace result_of {

// template <typename Tag, typename BaseIterator>
// struct dereference<Tag, BaseIterator
//                    , typename boost::enable_if
//                    <boost::mpl::and_<typename Tag::fixed_offset, typename Tag::fixed_size>
//                     , void>::type>
// {
//   typedef typename Tag::value_type type;
// };

// }

// template <typename Tag, typename BaseIterator>
// struct base_impl<Tag, BaseIterator, typename boost::enable_if<typename Tag::fixed_offset, void>::type>
// {
//   typedef typename Tag::context context_type;
//   static BaseIterator run(BaseIterator base_iterator, context_type context)
//   {
//     return boost::next(base_iterator, Tag::bits_offset::value/CHAR_BIT);
//   }
// };

// template <typename Tag, typename BaseIterator>
// struct dereference_impl<Tag, BaseIterator
//                         , typename boost::enable_if
//                         <boost::mpl::and_<typename Tag::fixed_offset, typename Tag::fixed_size>
//                          , void>::type>
// {
//   static typename Tag::value_type run(BaseIterator iterator, boost::mpl::void_)
//   {
//     return run(iterator, boost::mpl::size_t<CHAR_BIT>()
//                , typename boost::mpl::equal_to<typename Tag::bits_size, boost::mpl::size_t<CHAR_BIT> >::type()
//                , typename boost::mpl::less
//                    <boost::mpl::size_t<Tag::bits_size::value + (Tag::bits_offset::value % CHAR_BIT)>
//                     , boost::mpl::size_t<CHAR_BIT> >::type()
//                );
//   }

//   static typename Tag::value_type run(BaseIterator iterator, boost::mpl::size_t<8>, boost::mpl::true_
//                                       , boost::mpl::false_)
//   {
//     return iterator[Tag::bits_offset::value / CHAR_BIT];
//   }

//   static typename Tag::value_type run(BaseIterator iterator, boost::mpl::size_t<8>, boost::mpl::false_
//                                       , boost::mpl::true_)
//   {
//     typedef boost::mpl::size_t<Tag::bits_offset::value % CHAR_BIT> bits_remain;
//     typename Tag::value_type value = (iterator[Tag::bits_offset::value / CHAR_BIT]
//                                       >> (CHAR_BIT - Tag::bits_size::value - bits_remain::value))
//                                       & ((1 << Tag::bits_size::value) - 1);
//     return value;
//   }

//   static typename Tag::value_type run(BaseIterator iterator, boost::mpl::size_t<8>, boost::mpl::false_
//                                       , boost::mpl::false_)
//   {
//     typedef boost::mpl::size_t<Tag::bits_offset::value % CHAR_BIT> bits_remain;
//     typename Tag::value_type value;
//     BOOST_MPL_ASSERT_RELATION((Tag::bits_size::value + bits_remain::value)/CHAR_BIT, <=, sizeof(value));
// #if __LITTLE_ENDIAN == 1234
//     std::reverse_copy(boost::next(iterator, Tag::bits_offset::value / CHAR_BIT)
//                       , boost::next(iterator, (Tag::bits_offset::value
//                                                + bits_remain::value + Tag::bits_size::value)
//                                                / CHAR_BIT)
//                       , static_cast<unsigned char*>(static_cast<void*>(&value)));
// #else
//     std::copy(boost::next(iterator, Tag::bits_offset::value / CHAR_BIT)
//               , boost::next(iterator, (Tag::bits_offset::value
//                                        + bits_remain::value + Tag::bits_size::value)
//                                       / CHAR_BIT)
//               , static_cast<unsigned char*>(static_cast<void*>(&value)));
// #endif
//     value &= (1 << (Tag::bits_size::value)) - 1;
//     if(bits_remain::value + Tag::bits_size::value != sizeof(value)*CHAR_BIT)
//       value >>= sizeof(value)*CHAR_BIT - bits_remain::value + Tag::bits_size::value;
//     return value;
//   }
// };

// template <typename LeftTag, typename RightTag>
// struct is_equal_impl<LeftTag, RightTag
//                      , typename boost::enable_if
//                      <boost::mpl::and_<typename LeftTag::fixed_offset, typename RightTag::fixed_offset>
//                       , void>::type>
// {
//   template <typename BaseIterator>
//   static bool run(BaseIterator first, boost::mpl::void_, BaseIterator last, boost::mpl::void_)
//   {
//     typedef std::iterator_traits<BaseIterator> traits;
//     return first == last
//       && LeftTag::fixed_offset::value == RightTag::fixed_offset::value;
//   }
// };

// template <typename Tag, typename BaseIterator>
// struct tag_sequence_iterator : private Tag::context // EBO
// {
//   typedef typename Tag::context base_type;
//   tag_sequence_iterator(BaseIterator base_iterator, base_type c = base_type())
//     : base_type(c), base_iterator(base_iterator) {}

//   typename gts::result_of::dereference<Tag, BaseIterator>::type operator*() const
//   {
//     return gts::dereference_impl<Tag, BaseIterator>::run(base_iterator, context());
//   }

//   BaseIterator base() const
//   {
//     return gts::base_impl<Tag, BaseIterator>::run(base_iterator, context());
//   }

//   base_type const& context() const
//   {
//     return *this;
//   }
  
//   BaseIterator base_iterator;
// };

// template <typename LeftTag, typename RightTag, typename BaseIterator>
// bool operator==(tag_sequence_iterator<LeftTag, BaseIterator> lhs
//                 , tag_sequence_iterator<RightTag, BaseIterator> rhs)
// {
//   return is_equal_impl<LeftTag, RightTag>
//     ::run(lhs.base_iterator, lhs.context(), rhs.base_iterator, rhs.context());
// }

// template <typename LeftTag, typename RightTag, typename BaseIterator>
// bool operator!=(tag_sequence_iterator<LeftTag, BaseIterator> lhs
//                 , tag_sequence_iterator<RightTag, BaseIterator> rhs)
// {
//   return !(lhs == rhs);
// }

// namespace result_of {

// template <typename Tag, typename BaseIterator>
// struct next< ::gts::tag_sequence_iterator<Tag, BaseIterator>
//              , typename boost::enable_if
//              <boost::mpl::and_<typename Tag::fixed_offset, typename Tag::fixed_size>
//               , void>::type>
// {
//   typedef ::gts::tag_sequence_iterator<typename Tag::next_tag, BaseIterator> type;
// };

// }

// template <typename Tag, typename BaseIterator>
// struct next_impl<tag_sequence_iterator<Tag, BaseIterator>
//                  , typename boost::enable_if
//                  <boost::mpl::and_<typename Tag::fixed_offset, typename Tag::fixed_size>
//                   , void>::type>
// {
//   static tag_sequence_iterator<typename Tag::next_tag, BaseIterator>
//   run(tag_sequence_iterator<Tag, BaseIterator> iterator)
//   {
//     return tag_sequence_iterator<typename Tag::next_tag, BaseIterator>(iterator.base_iterator);
//   }
// };

// // template <typename ToTag, typename OldTag, typename BaseIterator>
// // tag_sequence_iterator<ToTag, BaseIterator> advance_to
// //  (tag_sequence_iterator<OldTag, BaseIterator> iterator)
// // {
// //   return tag_sequence_iterator<ToTag, BaseIterator>(iterator.base_iterator);
// // }

// }


#endif
