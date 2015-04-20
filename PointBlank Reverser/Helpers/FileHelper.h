#pragma once

#include "..\Includes.h"

class FileHelper
{
public:
	FileHelper(string lpFile);
	virtual int GetError();
	virtual HANDLE GetHandle();
	virtual DWORD GetSize();
	virtual PIMAGE_DOS_HEADER GetDOSHeader();
	virtual PIMAGE_NT_HEADERS GetNTHeaders();
	virtual PIMAGE_SECTION_HEADER GetSection(int ID);
	virtual PIMAGE_SECTION_HEADER GetSection(const char* lpName);
	virtual PIMAGE_SECTION_HEADER GetCodeSection();
	virtual DWORD GetBase();
	virtual DWORD UpdateBaseInAddr(DWORD dwAddr);
	template <typename t> t Read(DWORD Offset);
	void* Read(DWORD Offset, int size);
	template <typename t> void Write(DWORD Offset, t Value);
private:
	HANDLE hFile;
	void* pCode;
	int Error;
	DWORD FileSize;
};

template <typename t>
inline t FileHelper::Read(DWORD Offset)
{
	t* Result = (t*)VirtualAlloc(NULL, sizeof(t), MEM_COMMIT, PAGE_READWRITE);
	ZeroMemory(Result, sizeof(t));
	return *(t*)((DWORD)(pCode)+Offset);
}

template <typename t>
inline void FileHelper::Write(DWORD Offset, t Value)
{
	SetFilePointer(hFile, Offset, NULL, FILE_BEGIN);
	DWORD Written;
	WriteFile(hFile, (void*)&Value, sizeof(t), &Written, NULL);
}
