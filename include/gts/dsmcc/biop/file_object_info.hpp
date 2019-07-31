///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_BIOP_FILE_OBJECT_INFO_HPP
#define GTS_DSMCC_BIOP_FILE_OBJECT_INFO_HPP

namespace gts { namespace dsmcc { namespace biop {

template <typename BaseIterator>
struct file_object_info
{
  typedef boost::uint_t<64>::least content_size_type;
  file_object_info(content_size_type content_size
                   , boost::iterator_range<BaseIterator> rest)
    : content_size_(content_size), rest_(rest) {}

  content_size_type content_size() const { return content_size_; }
  boost::iterator_range<BaseIterator> rest() const { return rest_; }

  content_size_type content_size_;
  boost::iterator_range<BaseIterator> rest_;
};

} } }

#endif
