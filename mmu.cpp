#include "mmu.hpp" 

MMU::MMU(uint8_t *data) {
	memory = data;
}

uint8_t MMU::read(uint16_t addr) {
	return memory[addr];
}

void MMU::write(uint16_t addr, uint8_t b) {
	memory[addr] = b;
}
