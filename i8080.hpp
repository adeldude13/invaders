#ifndef I8080_HPP
#define I8080_HPP

#include <inttypes.h>
#include "bus.hpp"

typedef enum {
	C = (1 << 0),
	N = (1 << 1),
	P = (1 << 2),
	A = (1 << 4),
	Z = (1 << 6),
	S = (1 << 7),
	N1 = 1, // not used
	N0 = 0, // not used
} Flags;

class Bus;

class I8080 {
	public:
		I8080(Bus *);
		bool running = true;
		void setFlag(Flags, bool); 
		uint8_t getFlag(Flags);

		uint8_t read(uint16_t addr); 
		void write(uint16_t addr, uint8_t e);
		void push8(uint8_t), push16(uint16_t);
		uint8_t pop8();
		uint16_t pop16();

		uint16_t AF(), BC(), DE(), HL();
		void SET_AF(uint16_t), SET_BC(uint16_t), SET_DE(uint16_t), SET_HL(uint16_t);

		int run(uint64_t); 
		void execute(uint8_t); 
		bool INT = false, halted = false;
		void interrupt(int);
		uint64_t cycles = 0;

		/* instruction */ 
		void
		NOP(), LXI_B(), STAX_B(), INX_B(), INR_B(), DCR_B(), MVI_B(), RLC(), DAD_B(), LDAX_B(),
		DCX_B(), INR_C(), DCR_C(), MVI_C(), RRC(), LXI_D(), STAX_D(), INX_D(), INR_D(), DCR_D(),
		MVI_D(), RAL(), DAD_D(), LDAX_D(), DCX_D(), INR_E(), DCR_E(), MVI_E(), RAR(), LXI_H(),
		SHLD_ADR(), INX_H(), INR_H(), DCR_H(), MVI_H(), DAA(), DAD_H(), LHLD_ADR(), DCX_H(),
		INR_L(), DCR_L(), MVI_L(), CMA(), LXI_SP(), STA_ADR(), INX_SP(), INR_M(), DCR_M(),
		MVI_M(), STC(), DAD_SP(), LDA_ADR(), DCX_SP(), INR_A(), DCR_A(), MVI_A(), CMC(),
		MOV_B_B(), MOV_B_C(), MOV_B_D(), MOV_B_E(), MOV_B_H(), MOV_B_L(), MOV_B_M(), MOV_B_A(),
		MOV_C_B(), MOV_C_C(), MOV_C_D(), MOV_C_E(), MOV_C_H(), MOV_C_L(), MOV_C_M(), MOV_C_A(),
		MOV_D_B(), MOV_D_C(), MOV_D_D(), MOV_D_E(), MOV_D_H(), MOV_D_L(), MOV_D_M(), MOV_D_A(),
		MOV_E_B(), MOV_E_C(), MOV_E_D(), MOV_E_E(), MOV_E_H(), MOV_E_L(), MOV_E_M(), MOV_E_A(),
		MOV_H_B(), MOV_H_C(), MOV_H_D(), MOV_H_E(), MOV_H_H(), MOV_H_L(), MOV_H_M(), MOV_H_A(),
		MOV_L_B(), MOV_L_C(), MOV_L_D(), MOV_L_E(), MOV_L_H(), MOV_L_L(), MOV_L_M(), MOV_L_A(),
		MOV_M_B(), MOV_M_C(), MOV_M_D(), MOV_M_E(), MOV_M_H(), MOV_M_L(), MOV_M_M(), HLT(), MOV_M_A(),
		MOV_A_B(), MOV_A_C(), MOV_A_D(), MOV_A_E(), MOV_A_H(), MOV_A_L(), MOV_A_M(), MOV_A_A(), ADD_B(),
		ADD_C(), ADD_D(), ADD_E(), ADD_H(), ADD_L(), ADD_M(), ADD_A(), ADC_B(), ADC_C(), ADC_D(), ADC_E(),
		ADC_H(), ADC_L(), ADC_M(), ADC_A(), SUB_B(), SUB_C(), SUB_D(), SUB_E(), SUB_H(), SUB_L(), SUB_M(),
		SUB_A(), SBB_B(), SBB_C(), SBB_D(), SBB_E(), SBB_H(), SBB_L(), SBB_M(), SBB_A(), ANA_B(), ANA_C(),
		ANA_D(), ANA_E(), ANA_H(), ANA_L(), ANA_M(), ANA_A(), XRA_B(), XRA_C(), XRA_D(), XRA_E(), XRA_H(),
		XRA_L(), XRA_M(), XRA_A(), ORA_B(), ORA_C(), ORA_D(), ORA_E(), ORA_H(), ORA_L(), ORA_M(), ORA_A(),
		CMP_B(), CMP_C(), CMP_D(), CMP_E(), CMP_H(), CMP_L(), CMP_M(), CMP_A(), RNZ(), POP_B(), JNZ_ADR(),
		JMP_ADR(), CNZ_ADR(), PUSH_B(), ADI_D(), RST_0(), RZ(), RET(), JZ_ADR(), CZ_ADR(), CALL(), ACI_D(),
		RST_1(), RNC(), POP_D(), JNC_ADR(), OUT_D(), CNC_ADR(), PUSH_D(), SUI_D(), RST_2(), RC(), JC_ADR(),
		IN_D(), CC_ADR(), SBI_D(), RST_3(), RPO(), POP_H(), JPO_ADR(), XTHL(), CPO_ADR(), PUSH_H(), ANI_D(),
		RST_4(), RPE(), PCHL(), JPE_ADR(), XCHG(), CPE_ADR(), XRI_D(), RST_5(), RP(), POP_PSW(), ORI_D(),
		RST_6(), RM(), SPHL(), JM_ADR(), EI(), CM_ADR(), CPI_D(), RST_7(), JP_ADR(), DI(), CP_ADR(), PUSH_PSW();

	private:
		uint8_t a = 0, b = 0, c = 0, d = 0, e = 0, h = 0, l = 0;
		uint8_t f = 0;
		uint16_t pc = 0x0000, sp = 0xf000;
		Bus *bus;
};

#endif
