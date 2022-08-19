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

/* ================================= 0x20 ---- 0x2f ================================ */
// 0x20

void I::LXI_H() {
	l = read(pc++);
	h = read(pc++);
}

void I::SHLD_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	uint16_t addr = (hi << 8) | lo;
	l = read(addr);
	h = read(addr+1);
}

void I::INX_H() {
	SET_HL(HL()+1);
}

void I::INR_H() {
	h = h + 1;
	setFlag(Z, h == 0);
	setFlag(S, (h & 0x80) != 0);
	setFlag(P, PARITY(h));
}

void I::DCR_H() {
	h = h - 1;
	setFlag(Z, h == 0);
	setFlag(S, (h & 0x80) != 0);
	setFlag(P, PARITY(h));
}

void I::MVI_H() {
	h = read(pc++);
}

void I::DAA() {
	// TODO
}

void I::DAD_H() {
	// TODO	
}

void I::LDAX_D() {
	a = read(DE());
}

void I::DCX_D() {
	SET_DE(DE()-1);
}


void I::INR_L() {
	l = l + 1;
	setFlag(Z, l == 0);
	setFlag(S, (l & 0x80) != 0);
	setFlag(P, PARITY(l));
}

void I::DCR_L() {
	l = l - 1;
	setFlag(Z, l == 0);
	setFlag(S, (l & 0x80) != 0);
	setFlag(P, PARITY(l));
}

void I::MVI_L() {
	l = read(pc++);
}

void I::CMA() {
	a = ~a;
}


/* ================================= 0x30 ---- 0x3f ================================ */
// 0x30
//

void I::LXI_SP() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	sp = (hi << 8) | lo;
}

void I::STA_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	uint8_t addr = (hi << 8) | lo;
	a = read(addr);
}

void I::INX_SP() {
	sp++;
}

void I::INR_M() {
	write(HL(), read(HL()) + 1);
	uint8_t res = read(HL());
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res));
}

void I::DCR_M() {
	write(HL(), read(HL()) - 1);
	uint8_t res = read(HL());
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res));
}

void I::MVI_M() {
	write(HL(), read(pc++));
}

void I::STC() {
	setFlag(C, true);
}

void I::DAD_SP() {
	uint64_t res = HL() + sp;
	SET_HL(HL() + sp);
	setFlag(C, res > 0xFFFF);
}

void I::LDA_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	a = read((hi << 8) | lo);
}

void I::DCX_SP() {
	sp = sp - 1;
}

void I::INR_A() {
	a = a + 1;
	setFlag(Z, a == 0);
	setFlag(S, (a & 0x80) != 0);
	setFlag(P, PARITY(a));
}

void I::INR_A() {
	a = a - 1;
	setFlag(Z, a == 0);
	setFlag(S, (a & 0x80) != 0);
	setFlag(P, PARITY(a));
}

void I::MVI_A() {
	a = read(pc++);
}

void I::CMC() {
	setFlag(C, !getFlag(C));
}
