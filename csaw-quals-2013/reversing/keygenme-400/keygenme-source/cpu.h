#ifndef __CPU__
#define __CPU__
#include <string>
#include "instruction.h"
#define NUM_REG 32
#define MEM_SIZE 8196
class cpu
{
	typedef unsigned int uint;
	typedef unsigned char uchar;
public:
	cpu();
	cpu(std::string Code, std::string UserKey, std::string FullString);
	~cpu();
	void Execute();
	uint GetT6();
	uint GetT7();

private:
	uint R[NUM_REG]; //32
	uint Hi;
	uint Lo;
	uchar Memory[MEM_SIZE];
	uint Pc;
	instruction instr;
	std::string Code;
	std::string UserKey;
	uint hexval(char ch);
	uint hextoint(std::string hex);
	instruction interpretinstruction();
	void FillMemory(std::string UserKey, std::string FullString);
};
#endif
