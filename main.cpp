#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include "bus.hpp"
#include <SDL2/SDL.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 600

std::size_t size = 0;

uint8_t *readfile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		std::cout << "failed to read file " << filename;
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	uint8_t *code = new uint8_t[size];
	fread(code, size, 1, fp);
	fclose(fp);
	return code;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << argv[0] << " {Space Invaders ROM File}";
		return 1;
	}
	uint8_t *code = readfile(argv[1]);

	Bus bus = Bus((char*)"test", WIN_WIDTH, WIN_HEIGHT, code, size);
	uint32_t curr = SDL_GetTicks(); 
	uint32_t last = SDL_GetTicks();
	bus.run(0);
	// while(1) {
	// 	curr = SDL_GetTicks();
	// 	bus.run(curr-last);
	// 	last = curr;
	// }
	return 0;
}
