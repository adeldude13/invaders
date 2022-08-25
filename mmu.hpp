#ifndef MMU_HPP
#define MMU_HPP

#include <inttypes.h>

class MMU {
	public:
		MMU(uint8_t *);
		uint8_t read(uint16_t);
		void write(uint16_t, uint8_t);
	private:
		uint8_t *memory = nullptr;
};

#endif
