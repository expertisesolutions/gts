///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAMS_HAS_ES_BUFFER_HPP
#define GTS_PROGRAMS_HAS_ES_BUFFER_HPP

namespace gts { namespace programs {

template <typename Program, typename Enable = void>
struct has_es_buffer_impl
{
  static bool run(Program const& program, std::size_t pid)
  {
    return program.has_es_buffer(pid);
  }
};

template <typename Program>
bool has_es_buffer(Program const& program, std::size_t pid)
{
  return has_es_buffer_impl<Program>::run(program, pid);
}

} }

#endif
