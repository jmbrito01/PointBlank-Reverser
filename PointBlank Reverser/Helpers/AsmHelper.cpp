#include "AsmHelper.h"

AsmHelper::AsmHelper()
{
}

AsmHelper::~AsmHelper()
{
}

vector<DISASM> AsmHelper::Disassemble(DWORD dwAddr, int size)
{
	DISASM MyDisasm = { 0 };
	vector<DISASM> Result;
	int len, i = 0;
	int Error = 0;
	MyDisasm.EIP = dwAddr;
	while ((!Error) && (MyDisasm.EIP < dwAddr+size))
	{
		len = Disasm(&MyDisasm);
		if (len == UNKNOWN_OPCODE)
			len = 1;
		Result.push_back(MyDisasm);
		MyDisasm.EIP += len;
	}
	return Result;
}