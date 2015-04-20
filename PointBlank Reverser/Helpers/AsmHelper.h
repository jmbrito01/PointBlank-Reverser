#pragma once

#include "..\Includes.h"
#include "ProcessHelper.h"

static bool cbUnknown(const char* text, ULONGLONG* value)
{
	if (!text || !value)
		return false;
	cout << "ERROR PARSING THE COMMAND : \"" << text << "\"" << endl;
	return true;
}
class AsmHelper
{
public:
	AsmHelper();
	~AsmHelper();
	vector<DISASM> Disassemble(DWORD dwAddr, int size);
};

