// Windows Header Files:
#include <windows.h>
#include <shellapi.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ Runtime files
#include <iostream>
#include "Copernicus.h"

// Disable the console from popping up
// http://stackoverflow.com/a/6882500
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


// Random defines
#define IDI_SYSTRAYDEMO                 107
#define WM_USER_SHELLICON WM_USER + 1


// Button IDs used by the program (used in the callbacks)
#define IDM_PING                        104
#define IDM_EXIT                        105
#define IDM_ADMIN_PANEL                 106
#define IDM_DISABLE                     32778
#define IDM_ENABLE                      32779
#define IDM_STAT1                       32780
#define IDM_STAT2                       32781
#define IDM_STAT3                       32782
#define IDM_SEP                         32783


// Global Variables
MSG msg;
HINSTANCE hInst;
NOTIFYICONDATA nidApp;
Copernicus appCoper;

// Forward declarations of functions used in the main
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);