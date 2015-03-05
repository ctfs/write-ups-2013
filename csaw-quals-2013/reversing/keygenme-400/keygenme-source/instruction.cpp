#include "instruction.h"

instruction::instruction()
{
}

instruction::instruction(uint opcode, uint rs, uint rt, uint rd, uint immediate,
						 uint shift, uint funct, uint address)
{
	this->opcode = opcode;
	this->rs = rs;
	this->rt = rt;
	this->rd = rd;
	this->immediate = immediate;
	this->shift = shift;
	this->funct = funct;
	this->address = address;
}

instruction::~instruction()
{
}
