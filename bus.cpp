#include "bus.hpp"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#define FPS 59.541985
#define CLOCK_SPEED 1996800
#define CYCLES_PER_FRAME (CLOCK_SPEED / FPS)

Bus::Bus(char *name, int width, int height, uint8_t *code, uint16_t a) {
	// ports[0] = 0;
	// ports[1] = 0;
	// shift_offset = 0;
	// shift1 = 0;
	// shift0 = 0;
	// graphics = new Graphics(name, width, height, 224, 256);
	cpu = new I8080(this); // pass this bus to the cpu
	int i;
	for(i=0x100; i<a+0x100;i++) {
		memory[i] = code[i-0x100];
	}
	for(i=0;i<0x100;i++){
		memory[i] = 0;	
	}
	for(i=a+0x100;i<0x10000;i++){
		memory[i] = 0;
	}
	memory[0x0000] = 0xD3;
  memory[0x0001] = 0x00;
	memory[0x0005] = 0xD3;
  memory[0x0006] = 0x01;
  memory[0x0007] = 0xC9;
}

uint8_t Bus::read(uint16_t addr) {
	return memory[addr];
}

void Bus::write(uint16_t addr, uint8_t b) {
	memory[addr] = b;
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
	if( (ports[0] & 0x01) == 0x01) {
		std::cout << "Coin Inserted" << std::endl;
	}
}

void Bus::run(uint32_t dt) {
	// this->input();
	// uint64_t count = 0;
	// while(count < (dt * CLOCK_SPEED / 1000)) {
	// 	count += cpu->step();
	// 	if(cpu->cycles >= CYCLES_PER_FRAME / 2) {
	// 		cpu->cycles -= CYCLES_PER_FRAME / 2;
	// 		if(next_INT == 0x10) {
	// 			graphics->draw(&memory[0]);
	// 		}
	// 		cpu->interrupt(next_INT);
	// 		next_INT = (next_INT == 0x08) ? 0x10 : 0x08;
	// 	}
	// }
	// graphics->update();
	while(1) {
		cpu->dump();
		cpu->step();
	}
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
		default:
			std::cout << "Another Port!" << std::endl;
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
