#pragma once

#include "..\Includes.h"


class GUIObject
{
public:
	GUIObject();
	~GUIObject();
	HWND GetHandle();
	void SetHandle(HWND hWindow, int ID);
	void SetHandle(HWND hWindow);
	string GetText();
	int GetIntValue(BOOL bSigned = TRUE);
	void SetText(string text);
	void SetText(int i, bool bSigned = true);

	void Enable();
	void Disable();
	bool IsEnabled();
	bool IsDisabled();
private:
	HWND hWin;
};

