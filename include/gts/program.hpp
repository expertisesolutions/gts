///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAM_HPP
#define GTS_PROGRAM_HPP

#include <gts/programs/has_es_buffer.hpp>
#include <gts/programs/es_buffer.hpp>
#include <gts/pat_section_sequence.hpp>
#include <gts/pat_section_concept.hpp>

#include <boost/optional.hpp>

#include <memory>
#include <map>
#include <vector>

namespace gts {

template <typename TransportPacket>
struct es_buffer_base
{
  es_buffer_base() {}
  virtual ~es_buffer_base() {}
  virtual void push_packet(TransportPacket const& packet) = 0;
  virtual es_buffer_base* clone() const = 0;
protected:
  es_buffer_base(es_buffer_base const&) {}
  es_buffer_base& operator=(es_buffer_base const&) {}
};

template <typename TransportPacket>
struct es_buffer
{
  typedef gts::es_buffer_base<TransportPacket> es_buffer_base_type;

  es_buffer(es_buffer_base_type* es_buffer_impl)
    : es_buffer_impl(es_buffer_impl) {}

  typedef TransportPacket transport_packet_type;

  void push_packet(TransportPacket packet)
  {
    es_buffer_impl->push_packet(packet);
  }

  es_buffer(es_buffer const& other)
    : es_buffer_impl(other.es_buffer_impl->clone())
  {}
  es_buffer& operator=(es_buffer const& other)
  {
    es_buffer tmp(other);
    swap(tmp);
    return *this;
  }

  void swap(es_buffer& other)
  {
    std::swap(es_buffer_impl, other.es_buffer_impl);
  }

  es_buffer_base_type& impl() { return *es_buffer_impl; }
  es_buffer_base_type const& impl() const { return *es_buffer_impl; }
private:
  std::auto_ptr<es_buffer_base_type> es_buffer_impl;
};

template <typename TransportPacket>
struct pmt_buffer : es_buffer_base<TransportPacket>
{
  typedef TransportPacket packet_type;
  typedef pmt_buffer<packet_type> self_type;
  typedef es_buffer<packet_type> es_buffer_type;

  std::map<std::size_t, es_buffer_type> buffers;

  void push_packet(packet_type const& packet)
  {
    std::cout << "PMT packets" << std::endl;
  }

  self_type* clone() const
  {
    return new self_type(*this);
  }
};

template <typename TransportPacket>
struct pat_buffer : es_buffer_base<TransportPacket>
{
  typedef TransportPacket packet_type;
  typedef pat_buffer<packet_type> self_type;
  typedef es_buffer<packet_type> es_buffer_type;
  
  boost::optional<std::size_t> pmt_pid;
  std::map<std::size_t, es_buffer_type> buffers;

  void push_packet(packet_type const& packet)
  {
    std::cout << "PAT packet" << std::endl;
    packets.push_back(packet);

    typedef typename packet_type::sync_byte_iterator sync_byte_iterator;
    sync_byte_iterator sync_byte = packet.begin();
    assert(*sync_byte == 0x47);
    typedef typename packet_type::pid_iterator pid_iterator;
    pid_iterator pid = ++ ++ ++ ++sync_byte;
    assert(*pid == 0u);

    typedef pat_section_sequence<typename packet_type::base_iterator> pat_section_type;
    BOOST_CONCEPT_ASSERT((gts::PatSectionConcept<pat_section_type>));
    typedef typename packet_type::adaptation_field_control_iterator adaptation_field_control_iterator;
    adaptation_field_control_iterator adaptation_field_control
      = gts::iterators::next(gts::iterators::next(gts::iterators::next
        (gts::iterators::next(gts::iterators::next(gts::iterators::next
         (gts::sequences::begin(packet)))))));
    if(*adaptation_field_control & 0x1)
    {
      typedef typename packet_type::payload_iterator payload_iterator;
      payload_iterator payload
        = gts::iterators::next(gts::iterators::next(gts::iterators::next
          (adaptation_field_control)));
              
      typedef typename packet_type::base_iterator base_iterator;
      std::pair<base_iterator, base_iterator> p = *payload;
      pat_section_type pat_section(p.first, p.second);

      
    }
    else
    {
      std::cout << "No payload in PAT" << std::endl;
    }
  }

  self_type* clone() const
  {
    return new self_type(*this);
  }

  std::vector<packet_type> packets;
};

template <typename TransportPacket>
void swap(es_buffer<TransportPacket>& lhs, es_buffer<TransportPacket>& rhs)
{
  lhs.swap(rhs);
}

template <typename TransportPacket>
bool operator==(es_buffer<TransportPacket> const&, es_buffer<TransportPacket> const&)
{
  return true;
}

template <typename TransportPacket>
bool operator!=(es_buffer<TransportPacket> const& lhs, es_buffer<TransportPacket> const& rhs)
{
  return !(lhs == rhs);
}

template <typename TransportPacket>
struct program
{
  program()
    : pat_buffer_base(new gts::pat_buffer<TransportPacket>)
  {
  }

  typedef gts::es_buffer<TransportPacket> es_buffer_type;

  gts::pat_buffer<TransportPacket>& pat_buffer()
  {
    return static_cast<gts::pat_buffer<TransportPacket>&>(pat_buffer_base.impl());
  }
  gts::pat_buffer<TransportPacket>const& pat_buffer() const
  {
    return static_cast<gts::pat_buffer<TransportPacket>const&>(pat_buffer_base.impl());
  }
  bool has_pmt_buffer() const
  {
    return !!pat_buffer().pmt_pid;
  }

  std::map<std::size_t, es_buffer_type>& pat_buffers()
  {
    return pat_buffer().buffers;
  }
  std::map<std::size_t, es_buffer_type>const& pat_buffers() const
  {
    return pat_buffer().buffers;
  }

  bool has_es_buffer(std::size_t pid) const
  {
    return pid == 0 || pat_buffers().find(pid) != pat_buffers().end();
  }
  es_buffer_type& es_buffer(std::size_t pid)
  {
    assert(has_es_buffer(pid));
    if(pid == 0)
      return pat_buffer_base;
    else
      return pat_buffers().find(pid)->second;
  }

  es_buffer_type pat_buffer_base;
};

template <typename TransportPacket>
bool operator==(program<TransportPacket> const&, program<TransportPacket> const&)
{
  return true;
}

template <typename TransportPacket>
bool operator!=(program<TransportPacket> const& lhs, program<TransportPacket> const& rhs)
{
  return !(lhs == rhs);
}

}

#endif
