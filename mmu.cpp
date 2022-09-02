#include "mmu.hpp" 

MMU::MMU(uint8_t *data, uint16_t data_size, uint16_t size) {
	memory = new uint8_t[size];
	for(uint16_t i=0;i<size;i++) {
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
