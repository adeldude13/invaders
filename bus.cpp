#include "bus.hpp"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>


Bus::Bus(char *name, int width, int height, uint8_t *code, uint16_t a) {
	ports[0] = 0;
	ports[1] = 0;
	shift_offset = 0;
	shift1 = 0;
	shift0 = 0;
	graphics = new Graphics(name, width, height, 224, 256);
	cpu = new I8080(this); // pass this bus to the cpu
	int i;
	for(i=0; i<a;i++) {
		memory[i] = code[i];
	}
	for(i=a;i<0x10000;i++) {
		memory[i] = 0x0;
	}
}

uint8_t Bus::read(uint16_t addr) {
	if(addr >= 0x6000) {
		return 0;
	}
	if(addr >= 0x4000 && addr < 0x6000) {
		addr -= 0x2000;
	}
	return memory[addr];
}

void Bus::write(uint16_t addr, uint8_t b) {
	if(addr >= 0x2000 && addr < 0x4000) {
		memory[addr] = b;
	}
}

void Bus::input() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			std::cout << "Bye (:" << std::endl;
			exit(0);
		}
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_c: ports[0] |= 0x01; break;
				case SDLK_RETURN: ports[0] |= 0x04; break;
				case SDLK_SPACE: ports[0] |= 0x10; break;
				case SDLK_a: ports[0] |= 0x20; break;
				case SDLK_d: ports[0] |= 0x40; break;
			}
		}
		if(event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_c: ports[0] &= ~0x01; break;
				case SDLK_RETURN: ports[0] &= ~0x04; break;
				case SDLK_SPACE: ports[0] &= ~0x10; break;
				case SDLK_a: ports[0] &= ~0x20; break;
				case SDLK_d: ports[0] &= ~0x40; break;
			}
		}
	}
}

void Bus::run() {
	std::cout << "Starting Loop" << std::endl;
}


uint8_t Bus::in(int n) {
	uint8_t value = 0xFF;
	switch(n) {
		case 0:
			break;
		case 1:
		case 2:
			value = ports[n-1];
			break;
		case 3: {
			uint16_t v = (shift1<<8) | shift0;
			value = ((v >> (8-shift_offset)) & 0xff);
						}
		break;
	}
	return value;
}

void Bus::out(int n, uint8_t d) {
	switch(n) {
		case 2:
			shift_offset = d & 0x7;
			break;
		case 4:
			shift0 = shift1;
			shift1 = d;
			break;
	}
}
