#ifndef I8080_HPP
#define I8080_HPP

#include <inttypes.h>
#include "bus.hpp"

#define AF() ((a << 8) | f)
#define BC() ((b << 8) | c)
#define DE() ((d << 8) | e)
#define HL() ((h << 8) | l)
#define SET_AF(b) a = b >> 8; b = (b & 0xFF)
#define SET_BC(b) b = b >> 8; c = (b & 0xFF)
#define SET_DE(b) d = b >> 8; e = (b & 0xFF)
#define SET_HL(b) h = b >> 8; l = (b & 0xFF)

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
		void setFlag(Flags, bool); 
		uint8_t getFlag(Flags);
		uint8_t read(uint16_t addr); 
		void write(uint16_t addr, uint8_t e); 
	private:
		uint8_t a, b, c, d, e, h, l;
		uint8_t f;
		uint16_t pc, sp;
		Bus *bus;
};

#endif
