INCLUDEDIR := -I$(PWD)/include
GDB_DEBUG := -g
CFLAGS += $(INCLUDEDIR)
CFLAGS += $(GDB_DEBUG)
LOCAL_SRCS = $(wildcard *.c)
LOCAL_OBJS := $(patsubst %.c,%.o,$(LOCAL_SRCS))
.PHONY : all
all : $(LOCAL_OBJS) MV
$(LOCAL_OBJS) :%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
MV :
	mv ./$(LOCAL_OBJS) $(OBJS_DIR)
	
clean : 
	rm *.o
