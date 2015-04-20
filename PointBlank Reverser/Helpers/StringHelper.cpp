#include "StringHelper.h"



StringHelper::StringHelper()
{
}


StringHelper::~StringHelper()
{
}

DWORD StringHelper::StringToHex(string nHex)
{
	nHex.erase(0, 2);
	DWORD dwAddress = 0;
	for (int i = 0; i < nHex.size(); i++)
	{
		if (nHex[i] >= '0' && nHex[i] <= '9')
		{
			dwAddress += nHex[i] - 48;
			dwAddress *= 0x10;
		}
		else if (nHex[i] >= 'A' && nHex[i] <= 'F')
		{
			dwAddress += nHex[i] - 55;
			dwAddress *= 0x10;
		}
		else if (nHex[i] >= 'a' && nHex[i] <= 'f')
		{
			dwAddress += nHex[i] - 87;
			dwAddress *= 0x10;
		}
		else
		{
			return -1;
		}

	}
	return dwAddress / 0x10;
}

BYTE StringHelper::StringToByte(string nHex)
{
	if (nHex.length() > 4)
		return -1;
	return (BYTE)StringToHex(nHex);
}

string StringHelper::HexToString(DWORD dwHex)
{
	char* lpHex = new char[7];
	ZeroMemory(lpHex, 7);
	sprintf(lpHex, "0x%X", dwHex);
	return string(lpHex);
}

bool StringHelper::IsValidString(string nValue)
{
	if (nValue.size() <= 4)
		return false;
	for (int i = 0; i < nValue.size(); i++)
		if (!(nValue[i] >= 0x20) || !(nValue[i] <= 0x7E))
			return false;
	return true;
}
