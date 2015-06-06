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

#ifndef GTS_DSMCC_BIOP_CONN_BINDER_HPP
#define GTS_DSMCC_BIOP_CONN_BINDER_HPP

#include <boost/integer.hpp>

#include <vector>

namespace gts { namespace dsmcc { namespace biop {

struct tap
{
  boost::uint_t<16>::least id, use, assoc_tag;
  boost::uint_t<8>::least selector_length;
  boost::uint_t<16>::least selector_type;
  boost::uint_t<32>::least transaction_id, timeout;

  tap() : id(0), use(0), assoc_tag(0)
        , selector_length(0), selector_type(0)
        , transaction_id(0), timeout(0) {}
};

inline bool operator==(tap const& lhs, tap const& rhs)
{
  return lhs.id == rhs.id && lhs.use == rhs.use && lhs.assoc_tag == rhs.assoc_tag
    && lhs.selector_length == rhs.selector_length && lhs.selector_type == rhs.selector_type
    && lhs.transaction_id == rhs.transaction_id && lhs.timeout == rhs.timeout;
}

inline bool operator<(tap const& lhs, tap const& rhs)
{
  return
    lhs.id < rhs.id ||
    (lhs.id == rhs.id
     && (lhs.use < rhs.use ||
         (lhs.use == rhs.use
          && (lhs.assoc_tag < rhs.assoc_tag ||
              (lhs.assoc_tag == rhs.assoc_tag
               && (lhs.selector_length < rhs.selector_length ||
                   (lhs.selector_length == rhs.selector_length
                    && (lhs.selector_type < rhs.selector_type ||
                        (lhs.selector_type == rhs.selector_type
                         && (lhs.transaction_id < rhs.transaction_id ||
                             (lhs.transaction_id == rhs.transaction_id
                              && (lhs.timeout < rhs.timeout))))))))))));
}

struct conn_binder
{
  tap delivery_para_use_tap;
  std::vector<tap> taps;
};

inline bool operator==(conn_binder const& lhs, conn_binder const& rhs)
{
  return lhs.delivery_para_use_tap == rhs.delivery_para_use_tap
    && lhs.taps == rhs.taps;
}

inline bool operator<(conn_binder const& lhs, conn_binder const& rhs)
{
  return (lhs.delivery_para_use_tap == rhs.delivery_para_use_tap
          && lhs.taps < rhs.taps)
    || lhs.delivery_para_use_tap < rhs.delivery_para_use_tap;
}

} } }

#endif
