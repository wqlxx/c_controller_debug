#ifndef CC_SW_INFO_H
#define CC_SW_INFO_H 1

#include "cc_basic.h"
#include "cc_hash_table.h"
#include "queue.h"
#include "cc_single_link.h"
#include "cc_log.h"
#include "cc_xid.h"
#include "cc_thread_pool.h"

struct cc_socket_t{
	struct sockaddr_in cc_addr;
	//uint16_t port;
	int fd;
};
typedef struct cc_socket_t cc_socket;

struct port_info_t{
	struct ofp_phy_port port;
	int valid;
};
typedef struct port_info_t port_info;


struct each_sw_t{
	pid_t pid;
	uint64_t dpid;//datapath_id come from switch_feature_request/reply
	cc_socket cc_socket;
	//each_sw *next;
	char* profile_path;
	uint8_t version;
	uint32_t n_buffers;
	uint8_t n_tables;
	uint32_t actions;
	uint32_t capabilities;
	//port_info* port_head;
	port_info sw_port[CC_MAX_PORT];
};
typedef struct each_sw_t each_sw;


struct sw_info_t{
	each_sw cc_switch;
	pthread_t cc_sw_thread[CC_MAX_THREAD_NUM];

	CThread_pool* cc_recv_thread_pool;

	message_queue *send_queue;
  	message_queue *recv_queue;
	
	xid_table* xid_table_;
	uint32_t xid_latest;
	/*for app func to handle the msg send to app
	 *param: app_fd is the file description to connect to app server
	 *param: app_server_ip is the ip address of app server
	 *param: message to restore the app_msg to send to app server
	 */
	/*int app_fd;
	char* app_server_ip;
	message_queue *app_recv_queue;
	message_queue *app_send_queue;*/

	uint32_t cookie;

	/*set config*/
	uint16_t config_flags;        // OFPC_* flags
  	uint16_t miss_send_len;       /* Max bytes of new flow that datapath should
                                   send to the controller. */
								   	
};
typedef struct sw_info_t sw_info;
#endif// CC_OF_INFO_H

