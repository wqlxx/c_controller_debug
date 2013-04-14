/*
 * OpenFlow Switch Manager
 *
 * Copyright (C) 2008-2012 NEC Corporation
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


#ifndef OFPMSG_SEND_H
#define OFPMSG_SEND_H 1



#include "cc_basic.h"
#include "cc_of_msg_prep.h"
#include "cc_xid.h"
#include "cc_of_err.h"
#include "cc_of_action.h"
#include "cc_sw_info.h"
#include "cc_buffer.h"
#include "queue.h"
#include "cc_log.h"

#define OFP_ERROR_MSG_MAX_DATA 64

int cc_send_hello( sw_info* , buffer*);

int cc_send_echo_request( sw_info* , buffer*); 

int cc_send_echo_reply(sw_info* ,buffer*); 

int cc_send_features_request( sw_info* ,buffer*);

int cc_send_get_config_request(sw_info* , buffer*);

int cc_send_set_config(sw_info*, buffer*);

int cc_send_error_msg( sw_info* cc_sw_info, uint16_t type, uint16_t code, buffer *data ) ;

int cc_send_packet_out(sw_info* cc_sw_info, uint32_t buffer_id, uint16_t in_port, openflow_actions *actions, buffer* data);

int cc_send_port_mod(sw_info* cc_sw_info, 	uint16_t port_no,uint8_t hw_addr[OFP_ETH_ALEN], uint32_t config,uint32_t mask, uint32_t advertise);

int cc_send_stats_request(sw_info* cc_sw_info,uint16_t type, uint16_t length, uint16_t flags);

int cc_send_get_desc_stats(sw_info* cc_sw_info,	uint16_t flags);

int cc_send_flow_stats_request(sw_info* cc_sw_info, uint16_t flags, struct ofp_match match, uint8_t table_id,uint16_t out_port);

int cc_send_aggregate_stats_request(sw_info* cc_sw_info, uint16_t flags,struct ofp_match match, uint8_t table_id, uint16_t out_port);

int cc_send_table_stats_request(sw_info* cc_sw_info, uint16_t flags);

int cc_send_port_stats_request(sw_info* cc_sw_info, uint16_t flags, uint16_t port_no);

int cc_send_queue_stats_request(sw_info* cc_sw_info, uint16_t flags, uint16_t port_no, uint32_t queue_id);

int cc_send_vendor_stats_request(sw_info* cc_sw_info, uint16_t flags, uint32_t vendor, buffer* body);

int cc_send_flow_mod(sw_info* cc_sw_info, struct ofp_match match,uint64_t command,uint16_t idle_timeout, uint16_t hard_timeout,uint16_t priority, uint32_t buffer_id, uint16_t port, uint16_t flags,uint16_t out_port, openflow_actions *actions);

int cc_send_stats_request(sw_info* cc_sw_info,uint16_t type, uint16_t length, uint16_t flags);


#endif // OFPMSG_SEND_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */


