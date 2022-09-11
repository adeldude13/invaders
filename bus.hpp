#ifndef BUS_HPP
#define BUS_HPP

#include "i8080.hpp"
#include "graphics.hpp"

class I8080;
class Graphics;

class Bus {
	public:
		Bus(char *name, int width, int height, uint8_t *data, uint16_t);
		uint8_t read(uint16_t);
		void write(uint16_t addr, uint8_t b);
		void run();
		void draw();
		void input();
		uint8_t in(int);
		void out(int, uint8_t);
		uint8_t ports[2];
	private:
		uint8_t memory[0x10000];
		I8080 *cpu = nullptr;
		Graphics *graphics;
		uint8_t shift_offset, shift1, shift0;
};

#endif
