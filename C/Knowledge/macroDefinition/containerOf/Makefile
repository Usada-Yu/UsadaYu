COMPILER	:= gcc
target 		?= lovely
# coa对应不同文件。参数为analy和samp
coa			?= analy

TARGET		:= $(target)

ABSOLUTE_PATH	:= $(shell pwd)
BINARY_DIR		:= $(ABSOLUTE_PATH)/bin

ifeq ($(coa), analy)
SRC_FILES	:= $(ABSOLUTE_PATH)/containerOfAnalyse.c
else ifeq ($(coa), samp)
SRC_FILES	:= $(ABSOLUTE_PATH)/containerOfSample.c
endif
OBJ_FILES	:= $(patsubst $(ABSOLUTE_PATH)/%.c, $(ABSOLUTE_PATH)/%.o, $(SRC_FILES))

PHONY		+= default
default: mkdir $(TARGET)

PHONY		+= mkdir
mkdir:
	-@mkdir -p $(BINARY_DIR)

$(TARGET): $(OBJ_FILES)
	$(COMPILER) $(LDFLAGS) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	-@mv $(@) $(BINARY_DIR)

$(OBJ_FILES): $(SRC_FILES)
	$(COMPILER) $(CFLAGS) -o $(@) -c $(?)

PHONY		+= clean
clean:
	rm -rfv $(BINARY_DIR) *.o

.PHONY: $(PHONY)
