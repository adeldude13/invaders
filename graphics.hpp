#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>

#define HEIGHT 256
#define WIDTH 224

class Graphics {
	public:
		Graphics(char *, int, int, int, int);
		void draw(uint8_t *);
		void render();
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		uint8_t buf[HEIGHT][WIDTH][4];
};

#endif
