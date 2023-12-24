COMPILER	:= gcc
target 		?= lovely

TARGET		:= $(target)

TOPDIR		:= $(shell pwd)
BINARY_DIR	:= $(TOPDIR)/bin
INCLUDE_DIR	:= ../include

CFLAGS		+= -Wall

CFLAGS		+= -I$(INCLUDE_DIR)

SRC_FILES	:= $(shell find ./ -name "*.c" -exec echo {} +)
OBJ_FILES	:= $(patsubst ./%.c, ./%.o, $(SRC_FILES))

PHONY		+= default
default: mkdir $(TARGET)

PHONY		+= mkdir
mkdir:
	-@mkdir -p $(BINARY_DIR)

$(TARGET): $(OBJ_FILES)
	$(COMPILER) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	-@mv $(@) $(BINARY_DIR)

$(OBJ_FILES): $(SRC_FILES)
	$(COMPILER) $(CFLAGS) -o $(@) -c $(?)

PHONY		+= clean
clean:
	rm -rfv $(BINARY_DIR) *.o

.PHONY: $(PHONY)
