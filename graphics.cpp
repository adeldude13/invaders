#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>

#define VRAM_BASE 0x2400

#define REPORT(m) do {\
	std::cout << m << ": " << SDL_GetError() << std::endl; \
	exit(1); \
} while(0)
Graphics::Graphics(char *title, int ww, int wh, int vw, int vh) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		REPORT("SDL Failed To Init");
	}
	window = SDL_CreateWindow(title, 0, 0, ww, wh, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		REPORT("Failed to Create A Window");
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		REPORT("Failed to Create Renderer");
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, vw, vh);
	if(texture == NULL) {
		REPORT("Failed to Create Texture");
	}
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}
#undef REPORT

void Graphics::draw(uint8_t *code) {
	for(int i=0; i<WIDTH*HEIGHT/8;i++) {
		const int y = i * 8 / 256;
		const int x = (i * 8) % 256;
		uint8_t curbyte = code[VRAM_BASE + i];
		for(uint8_t shift=0; shift<8;shift++) {
			int px = x + shift;
			int py = y;
			bool isOn = (curbyte << shift) & 0x1;
			uint8_t v = isOn ? 255 : 0;
			int temp_x = px;
			px = py;
			py = -temp_x + HEIGHT - 1;
			buf[py][px][0] = v;
			buf[py][px][1] = v;
			buf[py][px][2] = v;
			buf[py][px][3] = v;
		}
	}
	this->render();
}

void Graphics::render() {
	int pitch = 0;
	void *pixels = NULL;
	if(SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
		std::cout << "Failed to Lock Texture" << std::endl;
		exit(0);
	}
	memcpy(pixels, buf, pitch * HEIGHT);
	SDL_UnlockTexture(texture);
}
