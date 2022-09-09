#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#include "mmu.hpp"

#define HEIGHT 256
#define WIDTH 224


#define REPORT(m) do {\
	std::cout << m << ": " << SDL_GetError() << std::endl; \
	exit(1); \
} while(0)
Graphics::Graphics(char *title, int ww, int wh, int vw, int vh) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		REPORT("SDL Failed To Init");
	}
	window = SDL_CreateWindow(title, 0, 0, ww, wh, SDL_WINDOW_RESIZABLE);
	if(window == NULL) {
		REPORT("Failed to Create A Window");
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		REPORT("Failed to Create Renderer");
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, vw, vh);
	if(texture == NULL) {
		REPORT("Failed to Create Texture");
	}
}
#undef REPORT

void Graphics::draw() {
	uint16_t i = 0x2400;
	for(int col=0; col<WIDTH;col++) {
		for(int row=HEIGHT; row>0;row-=8) {
			uint8_t bit = this->read(i);
			for(int j=0;j<8;j++) {
				int idx = (row - j) * WIDTH + col;
				if( bit & (1 << j) ) {
					buf[idx] = 0xFFFFFFFF;
				} else {
					buf[idx] = 0x00000000;
				}
			}
			i++;
		}
	}
	render();
}

void Graphics::render() {
	int p = sizeof(uint32_t) * WIDTH;
	SDL_UpdateTexture(texture, NULL, buf, p);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

uint8_t Graphics::read(uint16_t a) {
	return mem->read(a);
}

void Graphics::setMMU(MMU *m) {
	mem = m;
}
