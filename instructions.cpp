#include "i8080.hpp"

#define I I8080

bool PARITY(unsigned x) {
	int count = 0;
	
	for(count=0;x;x>>=1) { if(x&1) count++; }

	if(count & 1) {
		return false;
	}
	return true;
}

void I::NOP() {
	return;
}


void I::LXI_B_D() {
	c = read(pc++);
	b = read(pc++);
}

void I::STAX_B() {
	write(BC(), a);
}

void I::INX_B() {
	SET_BC(BC() + 1);

}

void I::INR_B() {
	b = b + 1;
	setFlag(Z, b == 0);
	setFlag(S, (b & 0x80) != 0);
	setFlag(P, PARITY(b));
}

void I::DCR_B() {
	b = b - 1;
	setFlag(Z, b == 0);
	setFlag(S, (b & 0x80) != 0);
	setFlag(P, PARITY(b));
}

void I::MVI_B() {
	b = read(pc++);
}

void I::RLC() {
	uint8_t prevSig = (a & 0x80);
	a = a << 1;
	a |= prevSig >> 7;
	setFlag(C, prevSig == 0x01);
}

void I::DAD_B() {
	uint16_t res = HL() + BC();
	setFlag(C, res > 255);
	SET_HL((uint16_t)HL() + (uint16_t)BC());
}

void I::LDAX_B() {
	a = read(BC());
}

void I::DCX_B() {
	SET_BC(BC() - 1);
}

void I::INR_C() {
	c = c + 1;
	setFlag(Z, c == 0);
	setFlag(S, (c & 0x80) != 0);
	setFlag(P, PARITY(c));
}

void I::INR_C() {
	c = c - 1;
	setFlag(Z, c == 0);
	setFlag(S, (c & 0x80) != 0);
	setFlag(P, PARITY(c));
}

void I::MVI_C() {
	c = read(pc++);
}

void I::RRC() {
	uint8_t prevBit = a & 0x01;
	a >>= 1;
	a |= prevBit << 7;
	setFlag(C, prevBit == 1);
}
