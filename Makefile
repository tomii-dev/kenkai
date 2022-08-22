CPPFLAGS := -std=c++14 $(INC_FLAGS) -Wall -g
INCFLAGS := -I./kenkai/include -I./deps/include
LIBS := sfml-graphics.2.5.1 sfml-window.2.5.1 sfml-system.2.5.1
LDFLAGS := -L./deps/lib $(addprefix -l,$(LIBS))
SRCS:= $(wildcard kenkai/src/*.cpp) \
	   $(wildcard kenkai/src/entities/*.cpp)

build:
	mkdir -p build
	g++ $(CPPFLAGS) $(SRCS) $(INCFLAGS) $(LDFLAGS) -o ./build/kenkai

clean:
	rm -rf build