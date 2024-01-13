plat		?= x86
jemalloc	?= true
# mtype对应src下的不同目录。参数为ctnu和stop
mtype		?= ctnu

CROSS		?=
CC			= $(CROSS)gcc

TOPDIR		:= $(shell pwd)
BINDIR_DIR	:= $(TOPDIR)/bin/$(plat)
LIB_DIR		:= $(TOPDIR)/lib/$(plat)
SRC_FILE_DIR:= $(TOPDIR)/src
SHARE_DIR	:= /share/$$USER/jemalloc/$(plat)

CFLAGS		+= -Wall
CFLAGS 		+= -O0 -g
CFLAGS		+= -I$(TOPDIR)/include

LDFLAGS		+= -L$(LIB_DIR)
LDFLAGS		+= -lpthread -ldl -lm -pthread -lstdc++

ifeq ($(mtype), ctnu)
	SRC_FILE_MEM_TYPE_DIR := $(SRC_FILE_DIR)/proCtnu
else ifeq ($(mtype), stop)
	SRC_FILE_MEM_TYPE_DIR := $(SRC_FILE_DIR)/proStop
endif

SRC_FILE_MEM_COMMON_DIR := $(SRC_FILE_DIR)/common

ifeq ($(jemalloc), true)
	LIBS	:= $(LIB_DIR)/libjemalloc.a
	LDFLAGS	+= -ljemalloc
endif

C_SOURCE_FILE	:= $(shell find $(SRC_FILE_MEM_COMMON_DIR) -name "*.c" -exec echo {} +)
C_SOURCE_FILE	+= $(shell find $(SRC_FILE_MEM_TYPE_DIR) -name "*.c" -exec echo {} +)
C_OBJ_FILES		+= $(patsubst $(SRC_FILE_DIR)/%.c,$(TOPDIR)/obj/$(plat)/%.o, $(C_SOURCE_FILE))
C_OBJ_DIR		:= $(shell echo $(dir $(C_OBJ_FILES)) | tr ' ' '\n' | sort -u | tr '\n' ' ')

TARGET	:= lovely

PHONY	:= default
default: mkdir pre $(TARGET)

PHONY	+= mkdir
mkdir:
	-@mkdir -p $(BINDIR_DIR)
	-@mkdir -p $(C_OBJ_DIR)
	-@mkdir -p $(SHARE_DIR)

PHONY	+= pre
pre:
	-@chmod 777 $(SHARE_DIR)

$(TARGET): $(C_OBJ_FILES) $(LIBS)
	$(CC) $(LDFLAGS) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	-@sudo xcp $(@) $(SHARE_DIR)
	mv $(@) $(BINDIR_DIR)

$(TOPDIR)/obj/$(plat)/%.o: $(SRC_FILE_DIR)/%.c
	$(CC) $(CFLAGS) -o $(@) -c $(?)

PHONY	+= clean
clean:
	rm -rfv $(TOPDIR)/bin $(TOPDIR)/obj $(TOPDIR)/memAnlys $(TOPDIR)/memReport

.PHONY: $(PHONY)
