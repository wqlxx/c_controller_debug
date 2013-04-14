/*
 * cc_secure_channel_send functions.
 *
 * Author: qiang wang <wqlxx@yahoo.com.cn>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
 
#ifndef CC_SOCKET_H
#define CC_SOKERT_H 1

#include "cc_basic.h"
#include "cc_xid.h"
#include "cc_of_msg_handler.h"
#include "cc_sw_info.h"
#include "cc_log.h"


#define CC_LISTEN_PORT 6633
#define CC_LENGTH_OF_LISTEN_QUEUE 20
//#define CC_TRY_CONN_TIMES 5
#define CC_ACCEPT_FD 3
#define CC_CHILD 1
#define CC_PARENT 0



int cc_close_socket(cc_socket *);
int cc_conn_accept(cc_socket*  ,sw_info* );
int cc_init_listenfd(cc_socket* );
int cc_client_socket_create(char *server_ip, uint16_t port);
#endif
