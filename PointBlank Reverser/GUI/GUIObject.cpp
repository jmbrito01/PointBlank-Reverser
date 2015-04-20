#include "GUIObject.h"



GUIObject::GUIObject()
{
}
GUIObject::~GUIObject()
{
}

HWND GUIObject::GetHandle()
{
	return hWin;
}
void GUIObject::SetHandle(HWND hWindow, int ID)
{
	hWin = GetDlgItem(hWindow, ID);
}
void GUIObject::SetHandle(HWND hWindow)
{
	hWin = hWindow;
}
string GUIObject::GetText()
{
	int len = GetWindowTextLength(hWin);
	char* lpChar = new char[len + 1];
	ZeroMemory(lpChar, len + 1);
	GetWindowText(hWin, lpChar, len+1);
	string lpFinal = string(lpChar);
	delete lpChar;
	return lpFinal;
}

int GUIObject::GetIntValue(BOOL bSigned)
{
	return GetDlgItemInt(GetParent(hWin), GetDlgCtrlID(hWin), NULL, bSigned);
}

void GUIObject::SetText(string text)
{
	SetWindowText(hWin, text.c_str());
}

void GUIObject::SetText(int i, bool bSigned)
{
	SetDlgItemInt(GetParent(hWin), GetDlgCtrlID(hWin), i, bSigned);
}

void GUIObject::Enable()
{
	EnableWindow(hWin, TRUE);
}

void GUIObject::Disable()
{
	EnableWindow(hWin, FALSE);
}

bool GUIObject::IsEnabled()
{
	return IsWindowEnabled(hWin);
}

bool GUIObject::IsDisabled()
{
	return !IsWindowEnabled(hWin);
}
