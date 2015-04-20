#include "GUIForm.h"



GUIForm::GUIForm(HWND hWindow, int ID)
{
	SetHandle(hWindow, ID);
}

#ifndef GUI_DLL
GUIForm::GUIForm(int ID, DLGPROC WindowProc, int initParam, HWND Parent)
{
	ExitCode = DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(ID), Parent, WindowProc, initParam);
}
#else
GUIForm::GUIForm(HINSTANCE hInstance, int ID, DLGPROC WindowProc, int initParam, HWND Parent)
{
	ExitCode = DialogBoxParam(hInstance, MAKEINTRESOURCE(ID), Parent, WindowProc, initParam);
}
#endif


void GUIForm::End(int ExitCode)
{
	EndDialog(GetHandle(), ExitCode);
}

GUIForm::~GUIForm()
{
}
