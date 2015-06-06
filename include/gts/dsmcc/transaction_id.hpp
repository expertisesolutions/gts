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

#ifndef GTS_DSMCC_TRANSACTION_ID_HPP
#define GTS_DSMCC_TRANSACTION_ID_HPP

#include <boost/integer.hpp>

#include <iosfwd>

namespace gts { namespace dsmcc {

// transaction_id: TR 101 202 V1.2.1 - 4.6.5 pg. 17
// DownloadInfoResponse & DownloadInfoIndication: 13818-6 - 7.3.2 pg. 257
// Getting Data Carousel Parameters: 13818-6 - 7.5.1 pg. 267
struct transaction_id
{
  transaction_id()
    : value(0u) {}
  transaction_id(boost::uint_t<32u>::least value)
    : value(value) {}

  bool update_flag() const
  {
    return value & 1;
  }

  boost::uint_t<15u>::least identification() const
  {
    return (value >> 1) & 0x7FFF;
  }

  boost::uint_t<14u>::least version() const
  {
    return (value >> 16) & 0x3FFF;
  }

  boost::uint_t<2u>::least originator() const
  {
    return (value >> 30) & 0x3;
  }

  boost::uint_t<32u>::least raw() const { return value; }
private:
  boost::uint_t<32u>::least value;
};

inline bool operator==(transaction_id const& lhs, transaction_id const& rhs)
{
  return lhs.raw() == rhs.raw();
}

inline bool operator!=(transaction_id const& lhs, transaction_id const& rhs)
{
  return !(lhs == rhs);
}

inline bool operator<(transaction_id const& lhs, transaction_id const& rhs)
{
  return lhs.raw() < rhs.raw();
}

inline bool operator>=(transaction_id const& lhs, transaction_id const& rhs)
{
  return !(lhs < rhs);
}

inline bool operator<=(transaction_id const& lhs, transaction_id const& rhs)
{
  return lhs < rhs || lhs == rhs;
}

inline bool operator>(transaction_id const& lhs, transaction_id const& rhs)
{
  return !(lhs <= rhs);
}

inline std::ostream& operator<<(std::ostream& os, transaction_id i)
{
  return os << i.raw();
}

} }

#endif
