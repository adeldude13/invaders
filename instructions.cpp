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

void I::ADD_B() {
	uint32_t result = (uint16_t)a + (uint16_t)b;
	a = a + b;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_C() {
	uint32_t result = (uint16_t)a + (uint16_t)c;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_D() {
	uint32_t result = (uint16_t)a + (uint16_t)d;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_E() {
	uint32_t result = (uint16_t)a + (uint16_t)e;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_H() {
	uint32_t result = (uint16_t)a + (uint16_t)h;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_L() {
	uint32_t result = (uint16_t)a + (uint16_t)l;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_M() {
	uint32_t result = (uint16_t)a + (uint16_t)read(HL());
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADD_A() {
	uint32_t result = (uint16_t)a + (uint16_t)a;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_B() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)b + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_C() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)c + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_D() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)d + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_E() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)e + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_H() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)h + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_L() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)l + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_M() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)read(HL()) + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::ADC_A() {
	uint16_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)a + cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

/* ================================= 0x90 ---- 0x9f ================================ */

void I::SUB_B() {
	uint32_t result = (uint16_t)a - (uint16_t)b;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_C() {
	uint32_t result = (uint16_t)a - (uint16_t)c;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_D() {
	uint32_t result = (uint16_t)a - (uint16_t)d;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_E() {
	uint32_t result = (uint16_t)a - (uint16_t)e;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_H() {
	uint32_t result = (uint16_t)a - (uint16_t)h;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_L() {
	uint32_t result = (uint16_t)a - (uint16_t)l;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_M() {
	uint32_t result = (uint16_t)a - (uint16_t)read(HL());
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_A() {
	uint32_t result = (uint16_t)a - (uint16_t)a;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_B() {
	uint8_t cyy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)b - cyy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_C() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)c - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_D() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)d - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_E() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)e - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_H() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)h - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_L() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)l - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_M() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)read(HL()) - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_A() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)a - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

/* ================================= 0xA0 ---- 0xAf ================================ */

void I::ANA_B() {
	 a &= b;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_C() {
	 a &= c;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_D() {
	 a &= d;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	 setFlag(P, PARITY(a));
}

void I::ANA_E() {
	 a &= e;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_H() {
	 a &= h;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_L() {
	 a &= l;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_M() {
	 a &= read(HL());
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ANA_A() {
	 a &= a;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_B() {
	 a ^= b;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_C() {
	 a ^= c;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_D() {
	 a ^= c;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_E() {
	 a ^= e;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_H() {
	 a ^= h;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_L() {
	 a ^= l;
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_M() {
 	a ^= read(HL());
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::XRA_A() {
	a ^= a;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

/* ================================= 0xB0 ---- 0xBf ================================ */

void I::ORA_B() {
 	a |= b;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_C() {
 	a |= c;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_D() {
 	a |= d;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_E() {
 	a |= e;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_H() {
 	a |= h;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_L() {
 	a |= l;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_M() {
 	a |= read(HL());
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::ORA_A() {
 	a |= a;
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::CMP_B() {
	uint16_t result = a - b;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_C() {
	uint16_t result = a - c;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_D() {
	uint16_t result = a - d;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_E() {
	uint16_t result = a - e;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_H() {
	uint16_t result = a - h;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_L() {
	uint16_t result = a - l;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_M() {
	uint16_t result = a - read(HL());
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::CMP_A() {
	uint16_t result = a - a;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

/* ================================= 0xC0 ---- 0xCf ================================ */

void I::RNZ() {
	if(!getFlag(Z)) {
		this->RET();
	}
}

void I::POP_B() {
	SET_BC(pop16());
}

void I::JNZ_ADR() {
	if(getFlag(Z)) {
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = (hi << 8) | lo;
	} else {
		pc+=2;
	}
}

void I::JMP_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	pc = (hi << 8) | lo;
}

void I::CNZ_ADR() {
	if(getFlag(Z)) {
		CALL();
	} else {
		pc+=2;
	}
}

void I::PUSH_B() {
	push16(BC());
}

void I::ADI_D() {
	uint8_t bytee = read(pc++);
	uint32_t result = (uint16_t)a + (uint16_t)bytee;
	a = a + bytee;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::RST_0() {
	push16(pc);
	pc = 0;
}

void I::RZ() {
	if(getFlag(Z)) {
		RET();
	}
}

void I::RET() {
	pc = pop16();
}

void I::JZ_ADR() {
	if(getFlag(Z)) {
		uint8_t lo = read(pc++);	
		uint8_t hi = read(pc++);
		pc = (hi << 8) | lo;
	} else {
		pc+=2;
	}
}

void I::CZ_ADR() {
	if(getFlag(Z)) {
		CALL();
	} else {
		pc+=2;
	}
}

void I::CALL() {
	push16(pc);
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	pc = (hi << 8) | lo;
}

void I::ACI_D() {
	uint8_t cy = getFlag(C);
	uint32_t result = (uint16_t)a + (uint16_t)bytee;
	a = a + bytee;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::RST_1() {
	push16(pc);
	pc = 0x0008;
}

void I::RNC() {
	if(!getFlag(C)) {
		RET();
	}
}

void I::POP_D() {
	SET_DE(pop16());
}

void I::JNC_ADR() {
	if(!getFlag(C)) {
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = (hi << 8) | lo;
	} else {
		pc+=2;
	}
}

void I::OUT_D() {
	// TODO
}

void I::CNC_ADR() {
	if(!getFlag(C)) {
		CALL();
	} else {
		pc+=2;	
	}
}

void I::PUSH_D() {
	push16(DE());
}

void I::SUI_D() {
	uint32_t result = (uint16_t)a - (uint16_t)read(pc++);
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, 0);
	setFlag(P, PARITY(a));
}

void I::RST_2() {
	push16(pc);
	pc = 0x0010;
}

void I::RC() {
	if(getFlag(C)) {
		RET();
	}
}

void I::JC_ADR() {
	if(getFlag(C)) {
		uint8_t lo = read(pc++);
		uint16_t hi = read(pc++) << 8;
		pc = hi | lo;
	} else {
		pc+=2;
	}
}

void I::IN_D() {
	// TODO
}

void I::CC_ADR() {
	if(getFlag(C)) {
		CALL();
	} else {
		pc+=2;
	}
}

void I::SBI_D() {
	uint8_t cyy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)b - cyy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::RST_3() {
	RST_2();
	pc = 0x0018;
}

void I::RPO() {
	if(!getFlag(P)) {
		pc = read(pc++) | (read(pc++) << 8);
	}
}

void I::POP_H() {
	SET_HL(pop16());
}

void I::JPO_ADR() {
	if(!getFlag(P)) {
		JMP_ADR();
	} else {
		pc+=2;
	}
}

void I::XTHL() {
	uint16_t temp = HL();
	SET_HL(pop16());
	push16(temp);
}

void I::CPO_ADR() {
	if(!getFlag(P)) {
		CALL();
	} else {
		pc+=2;
	}
}

void I::PUSH_H() {
	push16(HL());
}

void I::ANI_D() {
	 a &= read(pc++);
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	 setFlag(P, PARITY(P));
}

void I::RST_4() {
	pc = 0x0020;
}

void I::RPE() {
	if(getFlag(P)) {
		RET();
	}
}

void I::PCHL() {
	pc = HL();
}

void I::JPE_ADR() {
	if(getFlag(P)) {
		JMP_ADR();
	} else {
		pc+=2;
	}
}

void I::XCHG() {
	uint16_t temp = DE();
	SET_DE(HL());
	SET_HL(temp);
}

void I::CPE_ADR() {
	if(getFlag(P)) {
		CALL();
	} else {
		pc+=2;
	}
}

void I::XRI_D() {
	 a ^= read(pc++);
	 setFlag(Z, a==0);
	 setFlag(S, a & 0x80);
	 setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::RST_5() {
	pc = 0x0028;
}

void I::RP() {
	if(getFlag(P)) {
		RET();
	}
}

void I::RP() {
	if(getFlag(P)) {
		RET();
	}
}

void I::POP_PSW() {
	f = read(sp-2);
	a = read(sp-1);
	sp-=2;
}

void I::ORI_D() {
 	a |= read(pc++);
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
	setFlag(C, false);
	setFlag(P, PARITY(a));
}

void I::RST_6() {
	pc = 0x0030;
}

void I::RM() {
	pc+=2;	
}

void I::SPHL() {
	pc = HL();
}

void I::JM_ADR() {
	pc+=2;
}

void I::EI() {
	// TODO
}

void I::CM_ADR() {
	pc += 2;
}

void I::SBB_B() {
	uint8_t cyy = getFlag(C);
	uint32_t result = (uint16_t)a - (uint16_t)read(pc++) - cyy;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result));
}

void I::RST_7() {
	pc = 0x0038;
}
