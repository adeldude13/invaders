#include "bus.hpp"

Bus::Bus(uint8_t *code, uint16_t a, uint16_t b) {
	mmu = new MMU(code, a, b);
	cpu = new I8080(this); // pass this bus to the cpu
}

uint8_t Bus::read(uint16_t addr) {
	return mmu->read(addr);
}

void Bus::write(uint16_t addr, uint8_t b) {
	return mmu->write(addr, b);
}

void Bus::run() {
	cpu->loop();
}
