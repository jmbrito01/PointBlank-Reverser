#pragma once

#include "GUIObject.h"

class GUIProgressBar : public GUIObject
{
public:
	GUIProgressBar(HWND hWindow);
	GUIProgressBar(HWND hWindow, int ID);

	int GetPos();
	int GetStep();

	void SetPos(int i);
	void SetStep(int step);
	void SetRange(int min, int max);

	void Step();
~GUIProgressBar();
};

