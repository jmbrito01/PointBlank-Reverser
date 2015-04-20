#include "FileHelper.h"

FileHelper::FileHelper(string lpFile)
{
	ifstream file(lpFile.c_str(), ios::binary);
	if (file.is_open())
	{
		IMAGE_DOS_HEADER DOSHeader = { 0 };
		streampos begin, end;
		begin = file.tellg();
		file.seekg(0, ios::end);
		end = file.tellg();
		FileSize = end-begin;
		pCode = VirtualAlloc(NULL, end - begin, MEM_COMMIT, PAGE_READWRITE);
		ZeroMemory(pCode, end - begin);
		file.seekg(0, ios::beg);
		file.read((char*)pCode, end-begin);
		return;
	}
	else
	{
		MessageBox(0, "ERROR OPENING FILE.", 0, 0);
	}
	return;
}

int FileHelper::GetError()
{
	return Error;
}

HANDLE FileHelper::GetHandle()
{
	return hFile;
}

DWORD FileHelper::GetSize()
{
	return FileSize;
}

PIMAGE_DOS_HEADER FileHelper::GetDOSHeader()
{
	PIMAGE_DOS_HEADER Result = (PIMAGE_DOS_HEADER)(pCode);
	if (Result->e_magic == IMAGE_DOS_SIGNATURE)
		return Result;
	else
		return NULL;
}

PIMAGE_NT_HEADERS FileHelper::GetNTHeaders()
{
	PIMAGE_DOS_HEADER DOSHeader = GetDOSHeader();
	if (DOSHeader == NULL)
		return NULL;
	PIMAGE_NT_HEADERS NTHeaders = (PIMAGE_NT_HEADERS)((DWORD)DOSHeader + DOSHeader->e_lfanew);
	if (NTHeaders->Signature == IMAGE_NT_SIGNATURE)
		return NTHeaders;
	else
		return NULL;
}

PIMAGE_SECTION_HEADER FileHelper::GetSection(int ID)
{
	PIMAGE_NT_HEADERS NTHeaders = GetNTHeaders();
	if (NTHeaders == NULL)
		return NULL;
	return reinterpret_cast<PIMAGE_SECTION_HEADER>((DWORD)NTHeaders + sizeof(IMAGE_NT_HEADERS) + ID*sizeof(IMAGE_SECTION_HEADER));
}

PIMAGE_SECTION_HEADER FileHelper::GetSection(const char * lpName)
{
	for (int i = 0; i < GetNTHeaders()->FileHeader.NumberOfSections; i++)
		if (strcmp((char*)GetSection(i)->Name, lpName) == 0)
			return GetSection(i);
	return NULL;
}

PIMAGE_SECTION_HEADER FileHelper::GetCodeSection()
{
	return GetSection(0);
}

DWORD FileHelper::GetBase()
{
	return (DWORD)pCode;
}

DWORD FileHelper::UpdateBaseInAddr(DWORD dwAddr)
{
	DWORD Result = dwAddr;
	Result -= GetNTHeaders()->OptionalHeader.ImageBase;
	Result += GetBase();
	return Result;
}

void * FileHelper::Read(DWORD Offset, int size)
{
	SetFilePointer(hFile, Offset, NULL, FILE_BEGIN);
	void* Result = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
	memcpy(Result, (void*)((DWORD)(pCode)+Offset), size);
	return Result;
}
