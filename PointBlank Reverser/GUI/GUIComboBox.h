#pragma once

#include "GUIObject.h"
#include "GUIDefines.h"

class GUIComboBox : public GUIObject
{
public:
	GUIComboBox(HWND hWindow, int ID);

	void AddItem(string lpItem);

	void SetDropdownWidth(int w);

	int GetSelected();
	void SetSelected(int sel);
	void Clear();
	~GUIComboBox();
};

