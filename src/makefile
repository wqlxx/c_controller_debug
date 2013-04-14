INCLUDEDIR := -I$(PWD)/include
GDB_DEBUG := -g
CFLAGS += $(INCLUDEDIR)
CFLAGS += $(GDB_DEBUG)
LOCAL_OBJS = cc_main.o
.PHONY : all
all : $(LOCAL_OBJS) MV
$(LOCAL_OBJS) :%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
MV :
	mv ./$(LOCAL_OBJS) $(OBJS_DIR)	
