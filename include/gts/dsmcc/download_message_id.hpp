///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2011-2014 Felipe Magno de Almeida.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//

#ifndef GTS_DSMCC_DOWNLOAD_MESSAGE_ID_HPP
#define GTS_DSMCC_DOWNLOAD_MESSAGE_ID_HPP

namespace gts { namespace dsmcc {

namespace download_message_id {

enum download_message_id_type
{
  download_info_request = 0x1001
  , download_info_response = 0x1002
  , download_info_indication = 0x1002
  , download_data_block = 0x1003
  , download_data_request = 0x1004
  , download_data_cancel = 0x1005
  , download_server_initiate = 0x1006
};

}

} }

#endif
