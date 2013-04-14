#LOCAL_OBJS = $(wildcard *.o)
#TARGET = cc_main

#.PHONY : all
#all : $(TARGET) MV
#$(TARGET) : $(LOCAL_OBJS)
#	$(CC) -o $(TARGET) $(LOCAL_OBJS) -lpthread

#MV : 
#	mv ./$(TARGET) $(BIN_DIR)
TARGET = cc_main

.PHONY : $(TARGET) MV
$(TARGET) : cc_main.o cc_init_of.o cc_socket.o cc_of_msg_handler.o cc_secure_channel_recv.o cc_secure_channel_send.o cc_of_msg_send.o cc_of_msg_recv.o cc_of_msg_prep.o cc_of_action.o cc_xid.o cc_ether.o cc_packet.o cc_thread_pool.o cc_hash_table.o cc_utility.o cc_double_link.o cc_single_link.o cc_buffer.o queue.o cc_of_err.o cc_byte_order.o cc_log.o cc_random.o cc_sw_info_table.o cc_timer.o 

	$(CC) -o $@ $^ -lpthread

MV :
	$(warn "mv")
	mv $(TARGET) $(PWD)/bin
