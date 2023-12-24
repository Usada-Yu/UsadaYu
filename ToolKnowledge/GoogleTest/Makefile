plat		?= x86
TARGET		?= lovely

CROSS		?=
CPP			= $(CROSS)g++

TOPDIR		:= $(shell pwd)
BINARY_DIR	:= $(TOPDIR)/bin/$(plat)
GT_INC_DIR	:= $(TOPDIR)/../include
INCLUDE_DIR	:= $(TOPDIR)/include
LIB_DIR		:= $(TOPDIR)/../lib/$(plat)
SRC_FILE_DIR:= $(TOPDIR)/src

CFLAGS		+= -I$(GT_INC_DIR)
CFLAGS		+= -I$(INCLUDE_DIR)

LDFLAGS		+= -L$(LIB_DIR)
LDFLAGS		+= -lpthread -lgtest

LIBS		+= $(LIB_DIR)/libgtest.a

SRC_FILES	:= $(shell find $(TOPDIR) -name "*.cpp" -exec echo {} +)
OBJ_FILES	:= $(patsubst $(SRC_FILE_DIR)/%.cpp, $(SRC_FILE_DIR)/%.o, $(SRC_FILES))

PHONY		+= default
default: mkdir $(TARGET)

PHONY		+= mkdir
mkdir:
	-@mkdir -p $(BINARY_DIR)

$(TARGET): $(OBJ_FILES) $(LIBS)
	$(CPP) $(LDFLAGS) -o $(@) -Wl,--start-group $(?) -Wl,--end-group
	-@mv $(@) $(BINARY_DIR)

$(SRC_FILE_DIR)/%.o: $(SRC_FILE_DIR)/%.cpp
	$(CPP) $(CFLAGS) -o $(@) -c $(?)

PHONY		+= clean
clean:
	rm -rfv $(TOPDIR)/bin $(SRC_FILE_DIR)/*.o

.PHONY: $(PHONY)
