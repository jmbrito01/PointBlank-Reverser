#pragma once

#include "GUIObject.h"

class GUIButton : public GUIObject
{
public:
	GUIButton(HWND hWindow, int ID);
	~GUIButton();
};

