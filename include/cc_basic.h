/*
 * cc_of_msg_action functions.
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

#ifndef CC_BASIC_H
#define CC_BASIC_H 1

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <signal.h>
#include <limits.h>
#include <float.h>
#include <inttypes.h>
#include <stdarg.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "openflow.h"

#define CC_ERROR -1
#define CC_SUCCESS 0
#define CC_CONN_DOWN 1

#define CC_CONN_TIMEOUT_SEC 0
#define CC_CONN_TIMEOUT_USEC 0
/*used to temperaly to restrict the number \
*of linked switch,to make this project go easy
*/
#define CC_MAX_NUM_SWITCH 3

/*used in cc_thread_pool.c to \
*restrict the number of pthread
*/
#define CC_MAX_THREAD_NUM 3 

#define CC_BUFFER_SIZE (1024*sizeof(char))

#define FUNC_NAME __FUNCTION__

#define CC_TIMEOUT_FOR_HELLO 5
#define CC_TIMEOUT_FOR_ECHO_REPLY 5
#define CC_RECV_BUFFER_SIZE (USHRT_MAX+sizeof( struct ofp_packet_in )-2) 
#define CC_MAX_SOCKET_BUFF 3*1024*1024
#define CC_MAX_PORT 52

#define CC_DEFAULT_MISS_SEND_LEN 128
#define CC_DEFAULT_CONFIG_FLAGS 0

typedef int (*FUNC_CB)(void* cc_sw_info, void* buf);

enum ofp_app_type {
	OFPAPP_HELLO,
	OFPAPP_ECHO_REPLY,
	OFPAPP_ECHO_REQUEST,
	OFPAPP_ERROR,
	OFPAPP_FEATURE_REQUEST,
	OFPAPP_FLOW_MOD,
	OFPAPP_FLOW_STATS_REQUEST,
	OFPAPP_GET_CONFIG_REQUEST,
	OFPAPP_GET_DESC_STATS_REQUEST,
	OFPAPP_SET_CONFIG,
	OFPAPP_PORT_MOD,
	OFPAPP_PORT_STATS_REQUEST,
	OFPAPP_STATS_REQUEST,
	OFPAPP_TABLE_STATS_REQUEST,
	OFPAPP_VENDOR_STATS_REQUEST,
	OFPAPP_QUEUE_STATS_REQUEST,
	OFPAPP_AGGREGATE_STATS_REQUEST,
	OFPAPP_PACKET_OUT
};

#if 0
struct cc_socket{
	struct sockaddr_in cc_addr;
	//uint16_t port;
	int fd;
};
typedef struct cc_socket cc_socket;


struct xid_entry {
  uint32_t xid;
  struct timeval tv;
};
typedef struct xid_entry xid_entry;


struct xid_table {
  hash_table *xid_hash;
  list_element* xid_entry_list;
};
typedef struct xid_table xid_table;


struct port_info{
	struct ofp_phy_port port;
	int valid;
};
typedef struct port_info port_info;


struct each_sw{
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
typedef struct each_sw each_sw;

/**************************************************/


struct ofmsg_buf
{
    void* data;
    size_t length;
    void *user_data;
};
typedef struct ofmsg_buf ofmsg_buf;


struct worker   
{   
	void (*process)(void* arg, void* arg_);
    //void *(*process) (void *arg);   
    void *arg;/*回调函数的参数,recv_ofmsg*/  
    struct worker *next;   
};   
typedef struct worker CThread_worker;

  
struct CThread_pool
{   
    pthread_mutex_t queue_lock;   
	pthread_cond_t queue_ready;   
    
    CThread_worker *queue_head;   
  
    int shutdown;   
    pthread_t *threadid;  
	/*add 20130310*/
	pthread_attr_t *attr;
	/*end of add 20130310*/
    int max_thread_num;   
    int cur_queue_size;   
}; 
typedef struct CThread_pool CThread_pool;

struct event_handler{
	event_handler_callback read_handler;
	event_handler_callback write_handler;
	void* read_buf;
	void* write_buf;
};
typedef struct event_handler event_handler;


/*when the switch connect in,we should init the struct sw_info
**parm: send_queue and recv_queue should be init.
**parm: eh (event_handler)
**parm: xid_head should be NULL
**parm: 
*/
struct sw_info
{
	each_sw cc_switch;
	pthreat_t cc_sw_thread[CC_MAX_THREAD_NUM];

	//uint64_t datapathid;
	CThread_pool* cc_recv_thread_pool;
	//CThread_pool cc_send_thread_pool;	

	sw_state state;

	message_queue *send_queue;
  	message_queue *recv_queue;
	
	/* for xid hsah table
	 * param: xid_latest should be init to zero
	 * param: xid_table_ sholud be init by cc_init_xid_table
	 */
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

	/*set config*/
	uint16_t config_flags;        // OFPC_* flags
  	uint16_t miss_send_len;       /* Max bytes of new flow that datapath should
                                   send to the controller. */
}
typedef struct sw_info sw_info;

#endif //end of 0

//struct cc_socket listen_socket;

//typedef struct sw_queue cc_sw_queue;



#endif//END of cc_basic.h

