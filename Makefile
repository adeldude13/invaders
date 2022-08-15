CC := clang++
cfiles := main.cpp i8080.cpp bus.cpp mmu.cpp
hfiles := i8080.hpp bus.hpp mmu.hpp
files := $(cfiles) $(hfiles) Makefile
out := main
args := -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	$(CC) $(args) $(cfiles) && ./$(out)

clean:
	rm $(out)
