///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SEQUENCES_END_HPP
#define GTS_SEQUENCES_END_HPP

namespace gts { namespace sequences { namespace result_of {

template <typename Sequence, typename Enable = void>
struct end
{
  typedef typename Sequence::end_iterator type;
};

}

template <typename Sequence, typename Enable = void>
struct end_impl
{
  static typename sequences::result_of::end<Sequence>::type
  run(Sequence const& s)
  {
    return s.end();
  }
};

template <typename Sequence>
typename sequences::result_of::end<Sequence>::type end(Sequence const& s)
{
  return sequences::end_impl<Sequence>::run(s);
}

} }

#endif
