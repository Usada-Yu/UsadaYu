plat		?= x86
gcov		?= true

CROSS		?=
CC			= $(CROSS)gcc

TOPDIR				:= $(shell pwd)
BINDIR_DIR			:= $(TOPDIR)/bin/$(plat)
LIB_DIR				:= $(TOPDIR)/lib/$(plat)
SRC_FILE_DIR		:= $(TOPDIR)/src
COVERAGE_REPORT_DIR	:= $(TOPDIR)/coverage_report

CFLAGS		+= -Wall
CFLAGS 		+= -O0 -g

ifeq ($(gcov), true)
CFLAGS	+= --coverage
LDFLAGS	+= --coverage
# CFLAGS	+= -fprofile-arcs -ftest-coverage
# LDFLAGS	+= -fprofile-arcs
endif

C_SOURCE_FILE	:= $(shell find $(SRC_FILE_DIR) -name "*.c" -exec echo {} +)
C_OBJ_FILES		+= $(patsubst $(SRC_FILE_DIR)/%.c,$(TOPDIR)/obj/$(plat)/%.o, $(C_SOURCE_FILE))
C_OBJ_DIR		:= $(shell echo $(dir $(C_OBJ_FILES)) | tr ' ' '\n' | sort -u | tr '\n' ' ')

TARGET	:= lovely

PHONY	:= default
default: mkdir $(TARGET)

PHONY	+= mkdir
mkdir:
	-@mkdir -p $(BINDIR_DIR)
	-@mkdir -p $(C_OBJ_DIR)
	-@mkdir -p $(COVERAGE_REPORT_DIR)

$(TARGET): $(C_OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	mv $(@) $(BINDIR_DIR)

$(TOPDIR)/obj/$(plat)/%.o: $(SRC_FILE_DIR)/%.c
	$(CC) $(CFLAGS) -o $(@) -c $(?)

PHONY	+= clean
clean:
	rm -rfv $(TOPDIR)/bin $(TOPDIR)/obj $(TOPDIR)/coverage_report/*

.PHONY: $(PHONY)
