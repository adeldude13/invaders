#include "mmu.hpp" 
#include <iostream>

MMU::MMU(uint8_t *data, uint16_t data_size) {
	for(uint32_t i=0;i<0x10000;i++) {
		memory[i] = 0;
	}
	for(uint16_t i=0;i<data_size;i++) {
		memory[i] = data[i];
	}
}

uint8_t MMU::read(uint16_t addr) {
	return memory[addr];
}

void MMU::write(uint16_t addr, uint8_t b) {
	memory[addr] = b;
}
