TARGET_EXEC = kenkai
CC := g++
BUILD_DIR ?= ./build
SRCS:= $(wildcard src/*.cpp) \
	   $(wildcard src/Entities/*.cpp) \
	   $(wildcard src/UIElements/*.cpp) \
	   $(wildcard src/Menus/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)


INC_DIRS := ./include 
INC_DIRS += /opt/homebrew/Cellar/sfml/2.5.1_1/include /opt/homebrew/Cellar/boost/1.78.0_1/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIB_DIRS := /opt/homebrew/lib
LIBS := sfml-graphics sfml-window sfml-system boost_system boost_serialization
LDFLAGS := $(addprefix -L,$(LIB_DIRS)) $(addprefix -l,$(LIBS))

CPPFLAGS := -std=c++14 $(INC_FLAGS) -Wall -g

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
