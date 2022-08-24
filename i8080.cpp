#include "i8080.hpp"

I8080::I8080(Bus *b) {
	bus = b;
}

void I8080::setFlag(Flags flag, bool b) {
	if(b) {
		f |= flag;
		return;
	}
	f &= ~(flag);
}

uint8_t I8080::getFlag(Flags flag) {
	return f & flag;
}

uint8_t I8080::read(uint16_t addr) {
	return bus->read(addr);
}

void I8080::write(uint16_t addr, uint8_t b) {
	bus->write(addr, b);
}

void I8080::push8(uint8_t v) {
	write(sp-1, v);
	sp--;
}

void I8080::push16(uint16_t v) {
	push8(v & 0xff);
	push8(v >> 8);
}

uint8_t I8080::pop8() {
	return read(sp++);
}

uint16_t I8080::pop16() {
	return (pop8(sp) << 8) | pop8(sp);
}
