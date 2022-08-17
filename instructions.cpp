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

/* ================================= 0x00 ---- 0x0f ================================ */
void I::NOP() {
	return;
}


void I::LXI_B() {
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
	SET_HL(res);
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

/* ================================= 0x10 ---- 0x1f ================================ */

// 0x10 not impl
void I::LXI_D() {
	e = read(pc++);
	d = read(pc++);
}

void I::STAX_D() {
	write(DE(), a);
}

void I::INX_D() {
	SET_DE(DE()+1);
}

void I::INR_D() {
	d = d + 1;
	setFlag(Z, d == 0);
	setFlag(S, (d & 0x80) != 0);
	setFlag(P, PARITY(d));
}

void I::DCR_D() {
	d = d - 1;
	setFlag(Z, d == 0);
	setFlag(S, (d & 0x80) != 0);
	setFlag(P, PARITY(d));
}

void I::MVI_D() {
	d = read(pc++);
}

void I::RAL() {
	uint8_t prev = getFlag(C);
	uint8_t prevSig = a & 0x80;
	a <<= 1;
	a |= prev;
	setFlag(C, prevSig != 0);
}

// 0x18 // 


void I::DAD_B() {
	uint16_t res = HL() + DE();
	setFlag(C, res > 255);
	SET_HL(res);
}

void I::LDAX_D() {
	a = read(DE());
}

void I::DCX_D() {
	SET_DE(DE() - 1);
}

void I::INR_E() {
	e = e + 1;
	setFlag(Z, e == 0);
	setFlag(S, (e & 0x80) != 0);
	setFlag(P, PARITY(e));
}

void I::DCR_E() {
	e = e - 1;
	setFlag(Z, e == 0);
	setFlag(S, (e & 0x80) != 0);
	setFlag(P, PARITY(e));
}

void I::MVI_E() {
	e = read(pc++);
}

void I::RAR() {
	uint8_t prevSig = a & 0x80;
	uint8_t prevZ = a & 0x01;
	a >>= 1;
	a |= prevSig;
	setFlag(C, prevZ != 0);
}
