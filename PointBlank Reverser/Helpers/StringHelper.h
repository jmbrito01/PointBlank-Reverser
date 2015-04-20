#pragma once
#include "..\Includes.h"

class StringHelper
{
public:
	StringHelper();
~StringHelper();
public:
	static DWORD StringToHex(string nHex);
	static BYTE StringToByte(string nHex);
	static string HexToString(DWORD dwHex);
	static bool IsValidString(string nValue);
};

