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

/* ================================= 0x40 ---- 0x4f ================================ */

void I::MOV_B_B() {
	b = b;
}

void I::MOV_B_C() {
	b = c;
}

void I::MOV_B_D() {
	b = d;
}

void I::MOV_B_E() {
	b = e;
}

void I::MOV_B_H() {
	b = h;
}

void I::MOV_B_L() {
	b = l;
}

void I::MOV_B_M() {
	b = read(HL());
}

void I::MOV_B_A() {
	b = a;
}

void I::MOV_C_B() {
	c = b;
}

void I::MOV_C_C() {
	c = c;
}

void I::MOV_C_D() {
	c = d;
}

void I::MOV_C_E() {
	c = e;
}

void I::MOV_C_H() {
	c = h;
}

void I::MOV_C_L() {
	c = l;
}

void I::MOV_C_M() {
	c = read(HL());
}

void I::MOV_C_A() {
	c = a;
}

/* ================================= 0x50 ---- 0x5f ================================ */

void I::MOV_D_B() {
	d = b;
}

void I::MOV_D_C() {
	d = c;
}

void I::MOV_D_D() {
	d = d;
}

void I::MOV_D_E() {
	d = e;
}

void I::MOV_D_H() {
	d = h;
}

void I::MOV_D_L() {
	d = l;
}

void I::MOV_D_M() {
	d = read(HL());
}

void I::MOV_D_A() {
	d = a;
}

void I::MOV_E_B() {
	e = b;
}

void I::MOV_E_C() {
	e = c;
}

void I::MOV_E_D() {
	e = d;
}

void I::MOV_E_E() {
	e = e;
}

void I::MOV_E_H() {
	e = h;
}

void I::MOV_E_L() {
	e = l;
}

void I::MOV_E_M() {
	e = read(HL());
}

void I::MOV_E_A() {
	e = a;
}

/* ================================= 0x60 ---- 0x6f ================================ */

void I::MOV_H_B() {
	h = b;
}

void I::MOV_H_C() {
	h = c;
}

void I::MOV_H_D() {
	h = d;
}

void I::MOV_H_E() {
	h = e;
}

void I::MOV_H_H() {
	h = h;
}

void I::MOV_H_L() {
	h = l;
}

void I::MOV_H_M() {
	h = read(HL());
}

void I::MOV_H_A() {
	h = a;
}

void I::MOV_L_B() {
	l = b;
}

void I::MOV_L_C() {
	l = c;
}

void I::MOV_L_D() {
	l = d;
}

void I::MOV_L_E() {
	l = e;
}

void I::MOV_L_H() {
	l = h;
}

void I::MOV_L_L() {
	l = l;
}

void I::MOV_L_M() {
	l = read(HL());
}

void I::MOV_L_A() {
	l = a;
}

/* ================================= 0x70 ---- 0x7f ================================ */

void I::MOV_M_B() {
	write(HL(), b);
}

void I::MOV_M_C() {
	write(HL(), c);
}

void I::MOV_M_D() {
	write(HL(), d);
}

void I::MOV_M_E() {
	write(HL(), e);
}

void I::MOV_M_H() {
	write(HL(), h);
}

void I::MOV_M_L() {
	write(HL(), l);
}

void I::MOV_M_M() {
	write(HL(), read(HL()));
}

void I::HLT() {
	// TODO
}

void I::MOV_M_A() {
	write(HL(), a);
}

void I::MOV_A_B() {
	a = b;
}

void I::MOV_A_C() {
	a = c;
}

void I::MOV_A_D() {
	a = d;
}

void I::MOV_A_E() {
	a = e;
}

void I::MOV_A_H() {
	a = h;
}

void I::MOV_A_L() {
	a = l;
}

void I::MOV_A_M() {
	a = read(HL());
}

void I::MOV_A_A() {
	a = a;
}

/* ================================= 0x80 ---- 0x8f =============================== */
