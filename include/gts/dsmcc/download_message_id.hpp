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
