#ifndef BUS_HPP
#define BUS_HPP

#include "i8080.hpp"
#include "mmu.hpp"
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
		uint8_t in(int);
		void out(int, uint8_t);
		void input();
	private:
		I8080 *cpu = nullptr;
		MMU *mmu = nullptr;
		Graphics *graphics;
		uint8_t shift_offset, shift1, shift0;
		uint8_t ports[2];
};

#endif
