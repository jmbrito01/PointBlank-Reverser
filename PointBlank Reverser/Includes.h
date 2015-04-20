#pragma once

#define ACE_DEBUG

#define _CRT_SECURE_NO_WARNINGS

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <assert.h>
#include <Commctrl.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

#include "resource.h"

#include "Third-Party\BeaEngine\BeaEngine.h"

#pragma comment(lib, "Third-Party\\BeaEngine\\BeaEngine.lib")
#pragma comment(linker,                           \
    "\"/manifestdependency:type='Win32'"          \
    "   name='Microsoft.Windows.Common-Controls'" \
    "   version='6.0.0.0'"                        \
    "   processorArchitecture='*'"                \
    "   publicKeyToken='6595b64144ccf1df'"        \
    "   language='*'\""                           \
)
#pragma comment(lib, "ComCtl32.lib")

#pragma warning(disable: 4244 4018 4800 4458 4715)

using namespace std;

#define NEW_UNIQUE(a, b)			unique_ptr<a>(new b)