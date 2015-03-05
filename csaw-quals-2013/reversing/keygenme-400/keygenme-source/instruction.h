#ifndef __INSTRUCTION__
#define __INSTRUCTION__
#include <iostream>

class instruction
{
	typedef unsigned int uint;
public:
	instruction();
	instruction(uint opcode, uint rs, uint rt, uint rd, uint immediate, 
		uint shift,uint funct, uint address);
	~instruction();
	uint opcode;
	uint rs;
	uint rt;
	uint rd;
	uint immediate;
	uint shift;
	uint funct;
	uint address;
};

#endif