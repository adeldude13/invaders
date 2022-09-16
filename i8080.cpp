#include "i8080.hpp"
#include <iostream>
#include <stdio.h>

int OPCODES_CYCLES[256] = {
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4, 
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4, 
    4, 10, 16, 5,  5,  5,  7,  4,  4, 10, 16, 5,  5,  5,  7, 4, 
    4, 10, 13, 5,  10, 10, 10, 4,  4, 10, 13, 5,  5,  5,  7, 4, 
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5, 
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5, 
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5, 
    7, 7,  7,  7,  7,  7,  7,  7,  5, 5,  5,  5,  5,  5,  7, 5, 
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4, 
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4, 
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4, 
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4, 
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11,
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11,
    5, 10, 10, 18, 11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11,
    5, 10, 10, 4,  11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11 
};

I8080::I8080(Bus *b) {
	bus = b;
	pc = 0x100;
	sp = 0x0000;
	f = 1 << 1;
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
	return (uint16_t)(h << 8) | (uint16_t)l;
}

void I8080::SET_AF(uint16_t val) {
	a =  val >> 8;
	f =  val & 0xff;
}

void I8080::SET_BC(uint16_t val) {
	b = val >> 8;
	c = val & 0xff;
}

void I8080::SET_DE(uint16_t val) {
	d = val >> 8;
	e = val & 0xff;
}

void I8080::SET_HL(uint16_t val) {
	h = (val >> 8);
	l = val & 0xff;
}

int I8080::step() {
	if(halted) {
		std::cout << "Halted" << std::endl;
		return 0;
	}
	uint8_t opcode;
	ran++;
	opcode = read(pc++);
	this->execute(opcode);
	cycles += (uint64_t)OPCODES_CYCLES[opcode];
	return OPCODES_CYCLES[opcode];
}

void I8080::interrupt(uint8_t n) {
	if(INT) {
		push16(pc);
		pc = n;
		INT = false;
	}
}

void I8080::dump() {
	printf("PC: %04X, AF: %04X, BC: %04X, DE: %04X, HL: %04X, SP: %04X, CYC: %lu\n", pc, AF(), BC(), DE(), HL(), sp, cycles);
}
