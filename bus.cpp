#include "bus.hpp"

Bus::Bus(uint8_t *code) {
	mmu = new MMU(code);
	cpu = new I8080(this); // pass this bus to the cpu
}

uint8_t Bus::read(uint16_t addr) {
	return mmu->read(addr);
}

void Bus::write(uint16_t addr, uint8_t b) {
	return mmu->write(addr, b);
}
