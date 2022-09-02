#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include "bus.hpp"

uint8_t *readfile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		std::cout << "failed to read file " << filename;
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	std::size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	uint8_t *code = new uint8_t[size];
	fread(code, size, 1, fp);
	fclose(fp);
	return code;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << argv[0] << " {invaders rom}";
		return 1;
	}
	uint8_t *code = readfile(argv[1]);
	Bus bus(code, 0x1FFF, 0xFFFFu);
	bus.run();
	free(code);
	return 0;
}
