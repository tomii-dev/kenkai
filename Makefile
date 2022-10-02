CPPFLAGS := -std=c++17 $(INC_FLAGS) -Wall -g
INCFLAGS := -I./kenkai/include -I./deps/include
LIBS := sfml-graphics.2.5.1 sfml-window.2.5.1 sfml-system.2.5.1
LDFLAGS := -L./deps/lib $(addprefix -l,$(LIBS))
SRCS:= $(wildcard kenkai/src/*.cpp) \
	   $(wildcard kenkai/src/util/*.cpp) \
	   $(wildcard kenkai/src/component/*.cpp)

build:
	mkdir -p build
	g++ $(CPPFLAGS) $(SRCS) $(INCFLAGS) $(LDFLAGS) -o ./build/kenkai

clean:
	rm -rf build