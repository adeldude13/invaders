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
	push8(v >> 8);
	push8(v & 0xff);
}

uint8_t I8080::pop8() {
	return read(sp++);
}

uint16_t I8080::pop16() {
	uint8_t lo = pop8();
	uint8_t hi = pop8();
	return (hi << 8) | lo;
}

uint16_t I8080::AF() {
	return (a << 8) | f;
}

uint16_t I8080::BC() {
	return (b << 8) | c;
}

uint16_t I8080::DE() {
	return (d << 8) | e;
}

uint16_t I8080::HL() {
	return (h << 8) | l;
}

void I8080::SET_AF(uint16_t b) {
	a = b >> 8;
	f = b & 0xff;
}

void I8080::SET_BC(uint16_t b) {
	b = b >> 8;
	c = b & 0xff;
}

void I8080::SET_DE(uint16_t b) {
	d = b >> 8;
	e = b & 0xff;
}

void I8080::SET_HL(uint16_t b) {
	h = b >> 8;
	l = b & 0xff;
}

void I8080::loop(int n) {
	int count = 0;
	while(count < n || n == 0) {
		uint8_t opcode = read(pc++);
		this->execute(opcode);
		count++;
	}
}
