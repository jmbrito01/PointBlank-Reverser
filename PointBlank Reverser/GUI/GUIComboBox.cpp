#include "GUIComboBox.h"



GUIComboBox::GUIComboBox(HWND hWindow, int ID)
{
	SetHandle(hWindow, ID);
}


GUIComboBox::~GUIComboBox()
{
}

void GUIComboBox::AddItem(string lpItem)
{
	GUIMSG(CB_ADDSTRING, 0, lpItem.c_str());
}

void GUIComboBox::SetDropdownWidth(int w)
{
	GUIMSG(CB_SETDROPPEDWIDTH, w, w);
}

int GUIComboBox::GetSelected()
{
	return GUIMSG(CB_GETCURSEL, 0, 0);
}

void GUIComboBox::SetSelected(int sel)
{
	GUIMSG(CB_SETCURSEL, sel, 0);
}

void GUIComboBox::Clear()
{
	GUIMSG(CB_RESETCONTENT, 0, 0);
}