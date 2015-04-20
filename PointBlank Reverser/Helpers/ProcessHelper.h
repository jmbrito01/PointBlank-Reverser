#pragma once

#include "..\Includes.h"

class ProcessHelper
{
public:
	ProcessHelper(HANDLE hProc);

	DWORD GetImageBase();
	char* GetProcessName();
	void* Read(DWORD Address, DWORD size);
	template<typename t> t* Read(DWORD Address);
	template<typename t> void Write(DWORD Address, t value);
	int GetExternalStrLen(DWORD Address);
	DWORD GetSectionVirtualAddress(char* sectionName);
	DWORD GetSectionVirtualSize(char* sectionName);
	PIMAGE_DOS_HEADER GetDOSHeader();
	PIMAGE_NT_HEADERS GetNTHeaders();
	PIMAGE_SECTION_HEADER GetSectionHeader(int iSection);
	PIMAGE_SECTION_HEADER GetCodeSection();
	HANDLE GetHandle();
	~ProcessHelper();
public:
	static DWORD GetProcessIDbyName(char* lpName);

private:
	static string toLower(string s);
	HANDLE hProcess;
};

template <typename t>
inline t * ProcessHelper::Read(DWORD Address)
{
	t* result = (t*)VirtualAlloc(NULL, sizeof(t) + 1, MEM_COMMIT, PAGE_READWRITE);
	ZeroMemory(result, sizeof(result));
	ReadProcessMemory(hProcess, (void*)Address, (void*)result, sizeof(t), NULL);
	return result;
}

template <typename t>
inline void ProcessHelper::Write(DWORD Address, t value)
{
	WriteProcessMemory(hProcess, (void*)Address, (void*)&value, sizeof(value), NULL);
}
