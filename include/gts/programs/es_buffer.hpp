///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_PROGRAMS_ES_BUFFER_HPP
#define GTS_PROGRAMS_ES_BUFFER_HPP

namespace gts { namespace programs { namespace result_of {

template <typename Program, typename Enable = void>
struct es_buffer
{
  typedef typename Program::es_buffer_type type;
};

}

template <typename Program, typename Enable = void>
struct es_buffer_impl
{
  static typename programs::result_of::es_buffer<Program>::type
  run(Program& program, std::size_t pid)
  {
    return program.es_buffer(pid);
  }
};

template <typename Program>
typename programs::result_of::es_buffer<Program>::type es_buffer(Program& program, std::size_t pid)
{
  return es_buffer_impl<Program>::run(program, pid);
}

} }

#endif
