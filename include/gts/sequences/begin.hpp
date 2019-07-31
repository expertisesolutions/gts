///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_SEQUENCES_BEGIN_HPP
#define GTS_SEQUENCES_BEGIN_HPP

namespace gts { namespace sequences { namespace result_of {

template <typename Sequence, typename Enable = void>
struct begin
{
  typedef typename Sequence::begin_iterator type;
};

}

template <typename Sequence, typename Enable = void>
struct begin_impl
{
  static typename sequences::result_of::begin<Sequence>::type
  run(Sequence const& s)
  {
    return s.begin();
  }
};

template <typename Sequence>
typename sequences::result_of::begin<Sequence>::type begin(Sequence const& s)
{
  return sequences::begin_impl<Sequence>::run(s);
}

} }

#endif
