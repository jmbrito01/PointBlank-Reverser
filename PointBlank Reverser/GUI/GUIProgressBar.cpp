#include "GUIProgressBar.h"



GUIProgressBar::GUIProgressBar(HWND hWindow, int ID)
{
	SetHandle(hWindow, ID);
}


GUIProgressBar::GUIProgressBar(HWND hWindow)
{
	SetHandle(hWindow);
}

int GUIProgressBar::GetPos()
{
	return SendMessage(GetHandle(), PBM_GETPOS, 0, 0);
}

int GUIProgressBar::GetStep()
{
	return SendMessage(GetHandle(), PBM_GETSTEP, 0, 0);
}

void GUIProgressBar::SetPos(int i)
{
	SendMessage(GetHandle(), PBM_SETPOS, i, 0);
}

void GUIProgressBar::SetStep(int step)
{
	SendMessage(GetHandle(), PBM_SETSTEP, step, 0);
}

void GUIProgressBar::SetRange(int min, int max)
{
	SendMessage(GetHandle(), PBM_SETRANGE32, min, max);
}

void GUIProgressBar::Step()
{
	SendMessage(GetHandle(), PBM_STEPIT, 0, 0);
}

GUIProgressBar::~GUIProgressBar()
{
}
