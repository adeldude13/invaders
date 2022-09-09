#include "i8080.hpp"

#define I I8080

bool PARITY(uint8_t val) {
  uint8_t nb_one_bits = 0;
  for (int i = 0; i < 8; i++) {
    nb_one_bits += ((val >> i) & 1);
  }

  return (nb_one_bits & 1) == 0;
}

void I::execute(uint8_t ins) {
	if(ins == 0xD1) {
		POP_D();
		return;
	}
	switch(ins) {
		case 0x00: NOP(); break;
		case 0x01: LXI_B(); break;
		case 0x02: STAX_B(); break;
		case 0x03: INX_B(); break;
		case 0x04: INR_B(); break;
		case 0x05: DCR_B(); break;
		case 0x06: MVI_B(); break;
		case 0x07: RLC(); break;
		case 0x09: DAD_B(); break;
		case 0x0A: LDAX_B(); break;
		case 0x0B: DCX_B(); break;
		case 0x0C: INR_C(); break;
		case 0x0D: DCR_C(); break;
		case 0x0E: MVI_C(); break;
		case 0x0F: RRC(); break;
 

		case 0x11: LXI_D(); break;
		case 0x12: STAX_D(); break;
		case 0x13: INX_D(); break;
		case 0x14: INR_D(); break;
		case 0x15: DCR_D(); break;
		case 0x16: MVI_D(); break;
		case 0x17: RAL(); break;
		case 0x19: DAD_D(); break;
		case 0x1A: LDAX_D(); break;
		case 0x1B: DCX_D(); break;
		case 0x1C: INR_E(); break;
		case 0x1D: DCR_E(); break;
		case 0x1E: MVI_E(); break;
		case 0x1F: RAR(); break;
	

		case 0x21: LXI_H(); break;
		case 0x22: SHLD_ADR(); break;
		case 0x23: INX_H(); break;
		case 0x24: INR_H(); break;
		case 0x25: DCR_H(); break;
		case 0x26: MVI_H(); break;
		case 0x27: DAA(); break;
		case 0x29: DAD_H(); break;
		case 0x2A: LHLD_ADR(); break;
		case 0x2B: DCX_H(); break;
		case 0x2C: INR_L(); break;
		case 0x2D: DCR_L(); break;
		case 0x2E: MVI_L(); break;
		case 0x2F: CMA(); break;
		

		case 0x31: LXI_SP(); break;
		case 0x32: STA_ADR(); break;
		case 0x33: INX_SP(); break;
		case 0x34: INR_M(); break;
		case 0x35: DCR_M(); break;
		case 0x36: MVI_M(); break;
		case 0x37: STC(); break;
		case 0x39: DAD_SP(); break;
		case 0x3A: LDA_ADR(); break;
		case 0x3B: DCX_SP(); break;
		case 0x3C: INR_A(); break;
		case 0x3D: DCR_A(); break;
		case 0x3E: MVI_A(); break;
		case 0x3F: CMC(); break;


		case 0x40: MOV_B_B(); break;
		case 0x41: MOV_B_C(); break;
		case 0x42: MOV_B_D(); break;
		case 0x43: MOV_B_E(); break;
		case 0x44: MOV_B_H(); break;
		case 0x45: MOV_B_L(); break;
		case 0x46: MOV_B_M(); break;
		case 0x47: MOV_B_A(); break;
		case 0x48: MOV_C_B(); break;
		case 0x49: MOV_C_C(); break;
		case 0x4A: MOV_C_D(); break;
		case 0x4B: MOV_C_E(); break;
		case 0x4C: MOV_C_H(); break;
		case 0x4D: MOV_C_L(); break;
		case 0x4E: MOV_C_M(); break;
		case 0x4F: MOV_C_A(); break;

		case 0x50: MOV_D_B(); break;
		case 0x51: MOV_D_C(); break;
		case 0x52: MOV_D_D(); break;
		case 0x53: MOV_D_E(); break;
		case 0x54: MOV_D_H(); break;
		case 0x55: MOV_D_L(); break;
		case 0x56: MOV_D_M(); break;
		case 0x57: MOV_D_A(); break;
		case 0x58: MOV_E_B(); break;
		case 0x59: MOV_E_C(); break;
		case 0x5A: MOV_E_D(); break;
		case 0x5B: MOV_E_E(); break;
		case 0x5C: MOV_E_H(); break;
		case 0x5D: MOV_E_L(); break;
		case 0x5E: MOV_E_M(); break;
		case 0x5F: MOV_E_A(); break;


		case 0x60: MOV_H_B(); break;
		case 0x61: MOV_H_C(); break;
		case 0x62: MOV_H_D(); break;
		case 0x63: MOV_H_E(); break;
		case 0x64: MOV_H_H(); break;
		case 0x65: MOV_H_L(); break;
		case 0x66: MOV_H_M(); break;
		case 0x67: MOV_H_A(); break;
		case 0x68: MOV_L_B(); break;
		case 0x69: MOV_L_C(); break;
		case 0x6A: MOV_L_D(); break;
		case 0x6B: MOV_L_E(); break;
		case 0x6C: MOV_L_H(); break;
		case 0x6D: MOV_L_L(); break;
		case 0x6E: MOV_L_M(); break;
		case 0x6F: MOV_L_A(); break;


		case 0x70: MOV_M_B(); break;
		case 0x71: MOV_M_C(); break;
		case 0x72: MOV_M_D(); break;
		case 0x73: MOV_M_E(); break;
		case 0x74: MOV_M_H(); break;
		case 0x75: MOV_M_L(); break;
		case 0x76: HLT(); 		break;
		case 0x77: MOV_M_A(); break;
		case 0x78: MOV_A_B(); break;
		case 0x79: MOV_A_C(); break;
		case 0x7A: MOV_A_D(); break;
		case 0x7B: MOV_A_E(); break;
		case 0x7C: MOV_A_H(); break;
		case 0x7D: MOV_A_L(); break;
		case 0x7E: MOV_A_M(); break;
		case 0x7F: MOV_A_A(); break;


		case 0x80: ADD_B(); break;
		case 0x81: ADD_C(); break;
		case 0x82: ADD_D(); break;
		case 0x83: ADD_E(); break;
		case 0x84: ADD_H(); break;
		case 0x85: ADD_L(); break;
		case 0x86: ADD_M(); break;
		case 0x87: ADD_A(); break;
		case 0x88: ADC_B(); break;
		case 0x89: ADC_C(); break;
		case 0x8A: ADC_D(); break;
		case 0x8B: ADC_E(); break;
		case 0x8C: ADC_H(); break;
		case 0x8D: ADC_L(); break;
		case 0x8E: ADC_M(); break;
		case 0x8F: ADC_A(); break;

		
		case 0x90: SUB_B(); break;
		case 0x91: SUB_C(); break;
		case 0x92: SUB_D(); break;
		case 0x93: SUB_E(); break;
		case 0x94: SUB_H(); break;
		case 0x95: SUB_L(); break;
		case 0x96: SUB_M(); break;
		case 0x97: SUB_A(); break;
		case 0x98: SBB_B(); break;
		case 0x99: SBB_C(); break;
		case 0x9A: SBB_D(); break;
		case 0x9B: SBB_E(); break;
		case 0x9C: SBB_H(); break;
		case 0x9D: SBB_L(); break;
		case 0x9E: SBB_M(); break;
		case 0x9F: SBB_A(); break;

		
		case 0xA0: ANA_B(); break;
		case 0xA1: ANA_C(); break;
		case 0xA2: ANA_D(); break;
		case 0xA3: ANA_E(); break;
		case 0xA4: ANA_H(); break;
		case 0xA5: ANA_L(); break;
		case 0xA6: ANA_M(); break;
		case 0xA7: ANA_A(); break;
		case 0xA8: XRA_B(); break;
		case 0xA9: XRA_C(); break;
		case 0xAA: XRA_D(); break;
		case 0xAB: XRA_E(); break;
		case 0xAC: XRA_H(); break;
		case 0xAD: XRA_L(); break;
		case 0xAE: XRA_M(); break;
		case 0xAF: XRA_A(); break;


		case 0xB0: ORA_B(); break;
		case 0xB1: ORA_C(); break;
		case 0xB2: ORA_D(); break;
		case 0xB3: ORA_E(); break;
		case 0xB4: ORA_H(); break;
		case 0xB5: ORA_L(); break;
		case 0xB6: ORA_M(); break;
		case 0xB7: ORA_A(); break;
		case 0xB8: CMP_B(); break;
		case 0xB9: CMP_C(); break;
		case 0xBA: CMP_D(); break;
		case 0xBB: CMP_E(); break;
		case 0xBC: CMP_H(); break;
		case 0xBD: CMP_L(); break;
		case 0xBE: CMP_M(); break;
		case 0xBF: CMP_A(); break;


		case 0xC0: RNZ(); break;
		case 0xC1: POP_B(); break;
		case 0xC2: JNZ_ADR(); break;
		case 0xC3: JMP_ADR(); break;
		case 0xC4: CNZ_ADR(); break;
		case 0xC5: PUSH_B(); break;
		case 0xC6: ADI_D(); break;
		case 0xC7: RST_0(); break;
		case 0xC8: RZ(); break;
		case 0xC9: RET(); break;
		case 0xCA: JZ_ADR(); break;
		case 0xCB: NOP(); break;
		case 0xCC: CZ_ADR(); break;
		case 0xCD: CALL(); break;
		case 0xCE: ACI_D(); break;
		case 0xCF: RST_1(); break;


		case 0xD0: RNC(); break;
		case 0xD1: POP_D(); break;
		case 0xD2: JNC_ADR(); break;
		case 0xD3: OUT_D(); break;
		case 0xD4: CNC_ADR(); break;
		case 0xD5: PUSH_D(); break;
		case 0xD6: SUI_D(); break;
		case 0xD7: RST_2(); break;
		case 0xD8: RC(); break;
		case 0xD9: NOP(); break;
		case 0xDA: JC_ADR(); break;
		case 0xDB: IN_D(); break;
		case 0xDC: CC_ADR(); break;
		case 0xDD: NOP(); break;
		case 0xDE: SBI_D(); break;
		case 0xDF: RST_3(); break;


		case 0xE0: RPO(); break;
		case 0xE1: POP_H(); break;
		case 0xE2: JPO_ADR(); break;
		case 0xE3: XTHL(); break;
		case 0xE4: CPO_ADR(); break;
		case 0xE5: PUSH_H(); break;
		case 0xE6: ANI_D(); break;
		case 0xE7: RST_4(); break;
		case 0xE8: RPE(); break;
		case 0xE9: PCHL(); break;
		case 0xEA: JPE_ADR(); break;
		case 0xEB: XCHG(); break;
		case 0xEC: CPE_ADR(); break;
		case 0xED: NOP(); break;
		case 0xEE: XRI_D(); break;
		case 0xEF: RST_5(); break;


		case 0xF0: RP(); break;
		case 0xF1: POP_PSW(); break;
		case 0xF2: JP_ADR(); break;
		case 0xF3: DI(); break;
		case 0xF4: CP_ADR(); break;
		case 0xF5: PUSH_PSW(); break;
		case 0xF6: ORI_D(); break;
		case 0xF7: RST_6(); break;
		case 0xF8: RM(); break;
		case 0xF9: SPHL(); break;
		case 0xFA: JM_ADR(); break;
		case 0xFB: EI(); break;
		case 0xFC: CM_ADR(); break;
		case 0xFD: NOP(); break;
		case 0xFE: CPI_D(); break;
		case 0xFF: RST_7(); break;
	}
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
	uint16_t res = b + 1;
	setFlag(Z, (res&0xff) == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_B() {
	uint16_t res = b - 1;
	b = b - 1;
	setFlag(Z, (res&0xff) == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
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
	uint32_t res = HL() + BC();
	setFlag(C, res > 0xFFFF);
	SET_HL(res & 0xFFFF);
}

void I::LDAX_B() {
	a = read(BC());
}

void I::DCX_B() {
	SET_BC(BC() - 1);
}

void I::INR_C() {
	c = c + 1;
	uint16_t res = c + 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_C() {
	uint16_t res = c - 1;
	c = c - 1;
	setFlag(Z, (res & 0xFF) == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::MVI_C() {
	c = read(pc++);
}

void I::RRC() {
	uint8_t prevBit = a & 0x01;
	a >>= 1;
	a |= (prevBit << 7);
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
	uint16_t res = d + 1;
	d = d + 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_D() {
	uint16_t res = d - 1;
	d = d - 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
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


void I::DAD_D() {
	uint32_t res = HL() + DE();
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
	uint16_t res = e + 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_E() {
	e = e - 1;
	uint16_t res = e - 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
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
	uint16_t v = HL() + (uint16_t)1;
	SET_HL(v);
}

void I::INR_H() {
	h = h + 1;
	uint16_t res = h + 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_H() {
	h = h - 1;
	uint16_t res = h - 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::MVI_H() {
	h = read(pc++);
}

void I::DAA() {
	// TODO
}

void I::DAD_H() {
	uint32_t result = HL() + HL();
	SET_HL(result & 0xFFFF);
	setFlag(C, result > 0xFFFF);
}

void I::LHLD_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	uint16_t adr = (hi << 8) | lo;
	l = read(adr);
	l = read(adr+1);
}

void I::DCX_H() {
	SET_HL(HL()-1);
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
	write(addr, a);
}

void I::INX_SP() {
	sp++;
}

void I::INR_M() {
	uint32_t res = read(HL()) + 1;
	write(HL(), read(HL()) + 1);
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_M() {
	uint32_t res = read(HL()) + 1;
	write(HL(), read(HL()) - 1);
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
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
	setFlag(C, res > 255);
}

void I::LDA_ADR() {
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	uint16_t adr = (hi << 8) | lo;
	a = read(adr);
}

void I::DCX_SP() {
	sp = sp - 1;
}

void I::INR_A() {
	a = a + 1;
	uint32_t res = a + 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::DCR_A() {
	a = a - 1;
	uint32_t res = a - 1;
	setFlag(Z, res == 0);
	setFlag(S, (res & 0x80) != 0);
	setFlag(P, PARITY(res&0xff));
}

void I::MVI_A() {
	a = read(pc++);
}

void I::CMC() {
	setFlag(C, !getFlag(C));
}

/* ================================= 0x40 ---- 0x4f ================================ */

void I::MOV_B_B() {
	// b = b;
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
	// c = c;
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
	// d = d;
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
	// e = e;
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
	// h = h;
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
	// l = l;
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
	// a = a;
}

/* ================================= 0x80 ---- 0x8f =============================== */

void I::ADD_B() {
	uint16_t result = (uint16_t)a + (uint16_t)b;
	a = a + b;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_C() {
	uint16_t result = (uint16_t)a + (uint16_t)c;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_D() {
	uint16_t result = (uint16_t)a + (uint16_t)d;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_E() {
	uint16_t result = (uint16_t)a + (uint16_t)e;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_H() {
	uint16_t result = (uint16_t)a + (uint16_t)h;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_L() {
	uint16_t result = (uint16_t)a + (uint16_t)l;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_M() {
	uint16_t result = (uint16_t)a + (uint16_t)read(HL());
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADD_A() {
	uint16_t result = (uint16_t)a + (uint16_t)a;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_B() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)b + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_C() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)c + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result ));
}

void I::ADC_D() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)d + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result ));
}

void I::ADC_E() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)e + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_H() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)h + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_L() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)l + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_M() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)read(HL()) + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::ADC_A() {
	uint16_t cy = getFlag(C) ? 1 : 0;
	uint16_t result = (uint16_t)a + (uint16_t)a + cy;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

/* ================================= 0x90 ---- 0x9f ================================ */

void I::SUB_B() {
	uint16_t result = (uint16_t)a - (uint16_t)b;
	a = result & 0xff;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, b > a);
	setFlag(P, PARITY(result&0xff));
}

void I::SUB_C() {
	uint16_t result = (uint16_t)a - (uint16_t)c;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_D() {
	uint16_t result = (uint16_t)a - (uint16_t)d;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_E() {
	uint16_t result = (uint16_t)a - (uint16_t)e;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_H() {
	uint16_t result = (uint16_t)a - (uint16_t)h;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_L() {
	uint16_t result = (uint16_t)a - (uint16_t)l;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_M() {
	uint16_t result = (uint16_t)a - (uint16_t)read(HL());
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SUB_A() {
	uint16_t result = (uint16_t)a - (uint16_t)a;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_B() {
	uint8_t cyy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)b - cyy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_C() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)c - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_D() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)d - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_E() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)e - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_H() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)h - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_L() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)l - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_M() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)read(HL()) - cy;
	a = result & 0xff;
	setFlag(Z, a == 0);
	setFlag(S, a & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(a));
}

void I::SBB_A() {
	uint8_t cy = getFlag(C);
	uint16_t result = (uint16_t)a - (uint16_t)a - cy;
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
	setFlag(C, false);
	setFlag(Z, a==0);
	setFlag(S, a & 0x80);
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
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_C() {
	uint16_t result = a - c;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_D() {
	uint16_t result = a - d;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_E() {
	uint16_t result = a - e;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_H() {
	uint16_t result = a - h;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_L() {
	uint16_t result = a - l;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_M() {
	uint16_t result = a - read(HL());
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
}

void I::CMP_A() {
	uint16_t result = a - a;
	setFlag(Z, result == 0);
	setFlag(S, result & 0x80);
	setFlag(C, result > 0xff);
	setFlag(P, PARITY(result&0xff));
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
	if(!getFlag(Z)) {
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
	uint16_t result = (uint16_t)a + (uint16_t)bytee;
	a = result & 0xff;
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
	uint8_t lo = read(pc++);
	uint8_t hi = read(pc++);
	push16(pc);
	pc = (hi << 8) | lo;
}

void I::ACI_D() {
	uint8_t cy = getFlag(C);
	uint8_t bytee = read(pc++);
	uint16_t result = (uint16_t)a + (uint16_t)bytee + cy;
	a = result & 0xff;
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
	bus->out(read(pc++), a);
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
	uint16_t result = (uint16_t)a - (uint16_t)read(pc++);
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
	a = bus->in(read(pc++));
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
	uint16_t result = (uint16_t)a - (uint16_t)b - cyy;
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
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = (hi << 8) | (lo);
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

void I::POP_PSW() {
	SET_AF(pop16());
}

void I::JP_ADR() {
	if(getFlag(P)) {
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = (hi << 8) | lo;
	} else {
		pc++;
		pc++;
	}
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
	if(getFlag(S)) {
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = hi << 8;
		pc |= lo;
	} else {
		pc+=2;
	}
}

void I::EI() {
	INT = true;
}

void I::CM_ADR() {
	pc += 2;
}

void I::CPI_D() {
	uint8_t data = read(pc++);
	uint16_t result = (uint16_t)a - (uint16_t)data;
	setFlag(Z, result == 0);
	setFlag(S, (result & 0x80) == 0x80);
	setFlag(C, a < data);
	setFlag(P, PARITY(result&0xff));
}

void I::RST_7() {
	pc = 0x0038;
}

void I::DI() {
	// TODO
}

void I::CP_ADR() {
	if(getFlag(P)) {
		uint8_t lo = read(pc++);
		uint8_t hi = read(pc++);
		pc = (hi << 8) | lo;
	} else {
		pc += 2;
	}
}

void I::PUSH_PSW() {
	push16(AF());
}
