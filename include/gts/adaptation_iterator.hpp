///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_ADAPTATION_ITERATOR_HPP
#define GTS_ADAPTATION_ITERATOR_HPP

#include <gts/iterators/next.hpp>

namespace gts {

namespace adaptation_iterator_detail {

template <typename NextIterator>
struct default_next_iterator
{
  typedef NextIterator result_type;
  template <typename Sequence, typename CurrentAdapted>
  NextIterator operator()(Sequence const& sequence, CurrentAdapted const& current_adapted) const
  {
    return NextIterator(sequence, gts::iterators::next(current_adapted));
  }
};

template <typename AdaptedIterator, typename NextIterator
          , typename Sequence
          , typename NextIteratorF
          , typename ReuseNext>
struct first_base : AdaptedIterator
                  , private NextIteratorF
{
  typedef AdaptedIterator base_type;
  first_base(Sequence const& sequence, base_type base)
    : base_type(base), sequence(sequence) {}

  AdaptedIterator const& adapted_iterator () const { return *this; }

  typedef NextIterator next_type;
  NextIterator operator++() const
  {
    return static_cast<NextIteratorF const&>(*this)(sequence, adapted_iterator ());
  }

  Sequence const& sequence;
};

template <typename AdaptedIterator, typename NextIterator, typename Sequence, typename NextIteratorF>
struct first_base<AdaptedIterator, NextIterator, Sequence, NextIteratorF, boost::mpl::true_>
  : AdaptedIterator
{
  typedef AdaptedIterator base_type;
  first_base(Sequence const& sequence, base_type base)
    : base_type(base), sequence(sequence) {}

  Sequence const& sequence;
};

}

template <typename AdaptedIterator
          , typename Sequence
          , typename NextIterator = typename gts::iterators::result_of::next<AdaptedIterator>::type
          , typename Tag = void
          , typename NextIteratorF = adaptation_iterator_detail::default_next_iterator<NextIterator> >
struct adaptation_iterator : adaptation_iterator_detail::first_base
  <AdaptedIterator, NextIterator, Sequence, NextIteratorF
   , typename boost::is_same<typename gts::iterators::result_of::next<AdaptedIterator>::type
                             , NextIterator> >
{
  typedef adaptation_iterator_detail::first_base
  <AdaptedIterator, NextIterator, Sequence, NextIteratorF
   , typename boost::is_same<typename gts::iterators::result_of::next<AdaptedIterator>::type
                             , NextIterator> > first_base;
  adaptation_iterator(Sequence const& sequence, AdaptedIterator adapted_iterator)
    : first_base(sequence, adapted_iterator) {}

  typedef Sequence sequence_type;
  typedef AdaptedIterator adapted_iterator_type;
};

}

#endif
