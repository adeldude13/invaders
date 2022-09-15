CC := clang++
CFILES := main.cpp i8080.cpp instructions.cpp bus.cpp graphics.cpp
HFILES := i8080.hpp bus.hpp graphics.hpp
FILES := $(CFILES) $(HFILES) Makefile
OUT := main
LIBS := `pkg-config --cflags --libs sdl2`
ARGS := $(LIBS) -O0 -ggdb3 -Wall -Wextra -o $(OUT)

main: $(FILES)
	$(CC) $(ARGS) $(CFILES)

clean:
	rm $(OUT)
