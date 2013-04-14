CC := gcc
SUBDIRS := lib src obj
BIN := main
PWD := $(shell pwd)
OBJS_DIR := $(PWD)/obj
BIN_DIR := $(PWD)/bin
export CC PWD BIN OBJS_DIR BIN_DIR

all : CHECK_DIR $(SUBDIRS)
CHECK_DIR :
	mkdir -p $(BIN_DIR)
	
$(SUBDIRS) : ECHO
	make -C $@
	
ECHO :
	@echo $(SUBDIRS)
	@echo begin complie
	
CLEAN :
	@rm -rf $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)
