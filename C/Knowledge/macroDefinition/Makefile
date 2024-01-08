COMPILER	:= gcc
target 		?= lovely

TARGET		:= $(target)

ABSOLUTE_PATH	:= $(shell pwd)
BINARY_DIR		:= $(ABSOLUTE_PATH)/bin
INCLUDE_DIR		:= ../include

CFLAGS		+= -Wall

CFLAGS		+= -I$(INCLUDE_DIR)

SRC_FILES	:= $(shell find ./ -name "*.c" -exec echo {} +)
OBJ_FILES	:= $(patsubst ./%.c, ./%.o, $(SRC_FILES))

PHONY		+= debug release
debug: 		CFLAGS += -O0 -g
release:	CFLAGS += -O3

debug release: mkdir $(TARGET)

PHONY		+= mkdir
mkdir:
	-@mkdir -p $(BINARY_DIR)

$(TARGET): $(OBJ_FILES)
	$(COMPILER) $(CFLAGS) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	-@mv $(@) $(BINARY_DIR)

$(OBJ_FILES): $(SRC_FILES)
	$(COMPILER) $(CFLAGS) -o $(@) -c $(?)

PHONY		+= clean
clean:
	rm -rfv $(BINARY_DIR) *.o

.PHONY: $(PHONY)
