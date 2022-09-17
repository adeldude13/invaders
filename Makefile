CC := clang++
CFILES := src/main.cpp src/i8080.cpp src/instructions.cpp src/bus.cpp src/graphics.cpp
HFILES := src/i8080.hpp src/bus.hpp src/graphics.hpp
FILES := $(CFILES) $(HFILES) Makefile
OUT := bin/main
LIBS := `pkg-config --cflags --libs sdl2`
ARGS := $(LIBS) -O0 -ggdb3 -Wall -Wextra -o $(OUT)

main: $(FILES)
	$(CC) $(ARGS) $(CFILES)

clean:
	rm $(OUT)
