#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include "mmu.hpp"


class Graphics {
	public:
		Graphics(char *, int, int, int, int);
		void draw();
		void render();
		uint8_t read(uint16_t);
		void setMMU(MMU *);
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		MMU *mem;
		uint32_t buf[256*224];
};

#endif
