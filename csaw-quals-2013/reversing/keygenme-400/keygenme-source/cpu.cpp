#include "cpu.h"

typedef unsigned int uint;
typedef unsigned char uchar;
cpu::cpu()
{
}

cpu::cpu(std::string Code, std::string UserKey, std::string FullString)
{
	this->Code = Code;
	this->Pc = 0; //reset vector at 0
	for(int ii = 0; ii < NUM_REG; ii++)
	{
		this->R[ii] = 0;
	}
	for(int ii = 0; ii < MEM_SIZE; ii++)
	{
		this->Memory[ii] = 0;
	}
	FillMemory(UserKey, FullString);
}

cpu::~cpu()
{
}

void cpu::FillMemory(std::string UserKey, std::string FullString)
{
	for(int ii = 0; ii < 8; ii++)
	{
		Memory[ii] = UserKey[ii];
	}
	for(int ii = 0; ii < 16; ii++)
	{
		Memory[8+ii] = FullString[ii];
	}
}

uint cpu::GetT6()
{
	return R[14];
}

uint cpu::GetT7()
{
	return R[15];
}

uint cpu::hexval(char ch)
{
	switch(ch)
	{
	case 'a':
	case 'A':
		return 10;
	case 'b':
	case 'B':
		return 11;
	case 'c':
	case 'C':
		return 12;
	case 'd':
	case 'D':
		return 13;
	case 'e':
	case 'E':
		return 14;
	case 'f':
	case 'F':
		return 15;
	default:
		return (uint)(ch-'0');
	}
}

uint cpu::hextoint(std::string hex)
{
	uint retval = 0;
	int string_length = hex.length();
	for(int ii = 0; ii < string_length; ii++)
	{
		char ch = hex[(string_length - ii) - 1];
		uint multiplier = 1;
		uint chint = hexval(ch);
		for(int jj = 0; jj < ii; jj++)
		{
			multiplier *= 16;
		}
		retval +=  chint * multiplier;
	}
	return retval;
}

instruction cpu::interpretinstruction()
{
	instruction result;
	if(this->Pc > (this->Code.length() - 4))
	{
		result.opcode = 255;
		return result; //halt opcode because it's not enough to construct a complete instruction
	}
	result.opcode = (hextoint(this->Code.substr(this->Pc, 2))) >> 2; //bits 0-5
	result.rs = (hextoint(this->Code.substr(this->Pc + 1, 2)) >> 1) & 0x1F; //bits 6-10
	result.rt = (hextoint(this->Code.substr(this->Pc + 2, 2))) & 0x1F; //bits 11-15
	result.rd = hextoint(this->Code.substr(this->Pc + 4, 2)) >> 3; //bits 16-20
	result.shift = (hextoint(this->Code.substr(this->Pc + 5, 2)) >> 2) &0x1F; //bits 21-25
	result.funct = hextoint(this->Code.substr(this->Pc + 6, 2)) & 0x3F; //bits 26-31
	result.immediate = hextoint(this->Code.substr(this->Pc + 4, 4)); //bits 16-31
	result.address = hextoint(this->Code.substr(this->Pc + 1, 7)) & 0x3FFFFF; //bits 0-25
	this->Pc += 8;
	return result;
}

void cpu::Execute()
{
	instruction instr;
	while((instr = interpretinstruction()).opcode != 255)
	{
		switch (instr.opcode)
		{
		case 0x00: //R-Type operations
			{
				switch (instr.funct) //different R-Types all have the same opcode
				{
				case 0x20: //add
				case 0x21: //addu
					{
						this->R[instr.rd] = this->R[instr.rs] + this->R[instr.rt];
						break;
					}

				case 0x24: //and
					{
						this->R[instr.rd] = this->R[instr.rs] & this->R[instr.rt];
						break;
					}
				case 0x1A: //div
				case 0x1B: //divu
					{
						this->Lo = this->R[instr.rs] / this->R[instr.rt];
						this->Hi = this->R[instr.rs] % this->R[instr.rt];
						break;
					}

				case 0x08: //jr
					{
						this->Pc = this->R[instr.rs];
						break;
					}

				case 0x10: //mfhi
					{
						this->R[instr.rd] = this->Hi;
						break;
					}
				case 0x12: //mflo
					{
						this->R[instr.rd] = this->Lo;
						break;
					}

				case 0x18: //mult
				case 0x19: //multu
					{
						this->Lo = this->R[instr.rs] * this->R[instr.rt];
						break;
					}

				case 0x27: //nor
					{
						this->R[instr.rd] = ~(this->R[instr.rs] | this->R[instr.rt]);
						break;
					}

				case 0x26: //xor
					{
						this->R[instr.rd] = this->R[instr.rs] ^ this->R[instr.rt];
						break;
					}

				case 0x25: //or
					{
						this->R[instr.rd] = this->R[instr.rs] | this->R[instr.rt];
						break;
					}

				case 0x2A: //slt
					{
						this->R[instr.rd] = 0;
						if(this->R[instr.rs] < this->R[instr.rt])
						{
							this->R[instr.rd] = 1;
						}
						break;
					}

				case 0x2B: //sltu
					{
						this->R[instr.rd] = 0;
						if((uint)this->R[instr.rs] < (uint)this->R[instr.rt])
						{
							this->R[instr.rd] = 1;
						}
						break;
					}

				case 0x00: //sll
					{
						this->R[instr.rd] = this->R[instr.rt] << instr.shift;
						break;
					}

				case 0x02: //srl
					{
						this->R[instr.rd] = this->R[instr.rt] >> instr.shift;
						break;
					}

				case 0x03: //sra (omg, hax)
					{
						bool hax = false;
						if((this->R[instr.rt] & 0x8000000) != 0)
						{
							hax = true;
						}
						this->R[instr.rd] = this->R[instr.rt] >> instr.shift;
						if(hax)
						{
							int andme = -1;
							andme = andme << (32 - instr.shift);
							this->R[instr.rd] &= andme;
						}
						break;
					}

				case 0x22: //sub
					{
						this->R[instr.rd] = this->R[instr.rs] - this->R[instr.rt];
						break;
					}

				case 0x23: //subu
					{
						this->R[instr.rd] = (int)((uint)this->R[instr.rs] - (uint)this->R[instr.rt]);
						break;
					}

				default: //i don't know what the user tried to do here
					{
						break;
					}
				}

			}
			break;

		case 0x02: //j
			{
				this->Pc = ((this->Pc & 0xf0000000) | (instr.address << 2));
				break;
			}

		case 0x03: //jal
			{
				this->R[31] = this->Pc; //load up the linking register
				this->Pc = ((this->Pc & 0xf0000000) | (instr.address << 2));
				break;
			}	

		case 0x04: //beq branches are absolute in this cpu
			{
				if(this->R[instr.rs] == this->R[instr.rt])
				{
					this->Pc = instr.immediate << 3;
				}
				break;
			}

		case 0x05: //bne this is not done the "mips way" branches are absolute here
			{
				if(this->R[instr.rs] != this->R[instr.rt])
				{
					this->Pc = instr.immediate << 3;
				}
				break;
			}

		case 0x08: //addi
		case 0x09: //addiu
			{
				this->R[instr.rt] = this->R[instr.rs] + instr.immediate;
				break;
			}

		case 0x0A: //slti
		case 0x0B: //sltiu
			{
				if(this->R[instr.rs] < this->R[instr.immediate])
				{
					this->R[instr.rt] = 1;
				}
				else
				{
					this->R[instr.rt] = 0;
				}
				break;
			}

		case 0x0C: //andi
			{
				this->R[instr.rt] = this->R[instr.rs] & instr.immediate;
				break;
			}	

		case 0x0D: //ori
			{
				this->R[instr.rt] = this->R[instr.rs] | instr.immediate;
				break;
			}

		case 0x23: //lw
			{
				this->R[instr.rt] = (this->Memory[instr.immediate + instr.rs + 3]) +  
					(this->Memory[instr.immediate + instr.rs + 2] << 8) +  
					(this->Memory[instr.immediate + instr.rs + 1] << 16) +
					(this->Memory[instr.immediate + instr.rs] << 24);
				break;
			}

		case 0x24: //lbu
			{
				this->R[instr.rt] = this->Memory[instr.immediate + instr.rs];
				break;
			}

		case 0x25: //lhu
			{
				this->R[instr.rt] = (this->Memory[instr.immediate + instr.rs] << 8) + (this->Memory[instr.immediate + instr.rs + 1]);
				break;
			}	

		case 0x28: //sb
			{
				this->Memory[instr.immediate + instr.rs] = (uchar)(this->R[instr.rt] & 0xFF);
				break;
			}

		case 0x29: //shu
			{
				int stored = this->R[instr.rt];
				char ch[2];
				ch[0] = (stored >> 8) & 0xFF;
				ch[1] = stored & 0xFF;
				for(int ii = 0; ii < 2; ii++)
				{
					this->Memory[instr.immediate + instr.rs + ii] = ch[ii];
				}
				break;
			}

		case 0x2B: //sw
			{
				int stored = this->R[instr.rt];
				char ch[4];
				ch[0] = stored >> 24 & 0xFF;
				ch[1] = (stored >> 16) & 0xFF;
				ch[2] = (stored >> 8) & 0xFF;
				ch[3] = stored & 0xFF;
				for(int ii = 0; ii < 4; ii++)
				{
					this->Memory[instr.immediate + instr.rs + ii] = ch[ii];
				}
				break;
			}

		default:
			break;
		}
		this->R[0] = 0; //hardwired to 0. this is as close as I can get to that :-)
	}
	int x = 55;
}