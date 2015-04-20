#pragma once

#define GUIMSG(a,b,c)		SendMessage(GetHandle(), a, (WPARAM)b, (LPARAM)c)