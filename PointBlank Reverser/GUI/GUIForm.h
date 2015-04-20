#pragma once

#include "GUIObject.h"

class GUIForm : public GUIObject
{
public:
	GUIForm(HWND hWindow, int ID);
#ifndef GUI_DLL
	GUIForm(int ID, DLGPROC WindowProc, int initParam = 0, HWND Parent = HWND_DESKTOP);
#else
	GUIForm(HINSTANCE hInstance, int ID, DLGPROC WindowProc, int initParam = 0, HWND Parent = HWND_DESKTOP);
#endif
	void End(int ExitCode);
	~GUIForm();


private:
	int ExitCode;
};

