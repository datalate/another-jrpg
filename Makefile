src = $(wildcard src/*.cc)
obj = $(src:.cc=.o)

CC = g++
CPPFLAGS = -I./3rdparty/SDL2-2.0.8/include -I./3rdparty/SDL2_image-2.0.3/include
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
LDFLAGS = -lSDL2 -lSDL2_image

another-jrpg: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) another-jrpg

