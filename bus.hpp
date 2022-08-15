#ifndef BUS_HPP
#define BUS_HPP

#include "i8080.hpp"
#include "mmu.hpp"

class I8080;

class Bus {
	public:
		Bus(uint8_t *data);	
		uint8_t read(uint16_t);
		void write(uint16_t addr, uint8_t b);
	private:
		I8080 *cpu = nullptr;
		MMU *mmu = nullptr;
};

#endif
