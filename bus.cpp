#include "bus.hpp"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define TIC (1000.0 / 60.0)
#define CYCLES_PER_MS 2000
#define CYCLES_PER_TIC (TIC * CYCLES_PER_MS)

Bus::Bus(char *name, int width, int height, uint8_t *code, uint16_t a) {
	ports[0] = 0;
	ports[1] = 0;
	shift_offset = 0;
	shift1 = 0;
	shift0 = 0;
	graphics = new Graphics(name, width, height, 224, 256);
	mmu = new MMU(code, a);
	cpu = new I8080(this); // pass this bus to the cpu
	graphics->setMMU(mmu);
}

uint8_t Bus::read(uint16_t addr) {
	return mmu->read(addr);
}

void Bus::write(uint16_t addr, uint8_t b) {
	return mmu->write(addr, b);
}

void Bus::run() {
	uint32_t last_tic = SDL_GetTicks();	
	while(1) {
		if((SDL_GetTicks() - last_tic) >= TIC) {
			last_tic = SDL_GetTicks();
			cpu->loop(CYCLES_PER_TIC/2);
			if(cpu->INT) {
				cpu->interrupt(0x08);
			}
			cpu->loop(CYCLES_PER_TIC/2);
			this->input();
			graphics->draw();
			if(cpu->INT) {
				cpu->interrupt(0x10);
			}
		}
	}
}

void Bus::input() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case 'c':
						ports[0] |= 1;
						break;
					case 's':
						ports[0] |= 1 << 2;
						break;
					case 'w':
						ports[0] |= 1 << 4;
						break;
					case 'a':
						ports[0] |= 1 << 5;
						break;
					case 'd':
						ports[0] |= 1 << 6;
						break;
					case SDLK_LEFT:
						ports[1] |= 1 << 5;
						break;
					case SDLK_RIGHT:
						ports[1] |= 1 << 6;
						break;
					case SDLK_RETURN:
						ports[1] |= 1 << 1;
						break;
					case SDLK_UP:
						ports[1] |= 1 << 4;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
						case 'c':
						ports[0] &= ~1;
						break;
					case 's':
						ports[0] &= ~(1 << 2);
						break;
					case 'w':
						ports[0] &= ~(1 << 4);
						break;
					case 'a':
						ports[0] &= ~(1 << 5);
						break;
					case 'd':
						ports[0] &= ~(1 << 6);
						break;
					case SDLK_LEFT:
						ports[1] &= ~(1 << 5);
						break;
					case SDLK_RIGHT:
						ports[1] &= ~(1 << 6);
						break;
					case SDLK_RETURN:
						ports[1] &= ~(1 << 1);
						break;
					case SDLK_UP:
						ports[1] &= ~(1 << 4);
						break;
				}
			break;
			case SDL_QUIT:
				exit(0);
				break;
		}
	}
}


uint8_t Bus::in(int n) {
	uint8_t value;
	switch(n) {
		case 1:
		case 2:
			value = ports[n-1];
			break;
		case 3: {
			uint16_t v = (shift1<<8) | shift0;
			value = ((v >> (8-shift_offset)) & 0xff);
						}
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
