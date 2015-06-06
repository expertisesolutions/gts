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
