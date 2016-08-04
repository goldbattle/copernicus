/**
 * Copernicus a Windows Client for the Pi-Hole advertising-aware DNS/web server
 * Copyright (C) 2016  Patrick Geneva
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {

  // Debug
  std::cout << "[debug]: Windows Main Function Called" << std::endl;

  // The do something, not sure what
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  
  // Register our window class
  std::cout << "[debug]: Registering Our Window Class" << std::endl;
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow)) {
    std::cerr << "[error]: Unable to Create Window" << std::endl;
    return FALSE;
  }

  // Success
  std::cout << "[debug]: Window Has Been Created" << std::endl;

  // The main message loop
  while (GetMessage(&msg, NULL, 0, 0)) {
    // For now, if we get a message, lets process it
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }


  // Cleanup, and shutdown
  std::cout << "[debug]: Clean Exit, Shutting Down" << std::endl;
  return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {

  // Icons
  HICON hMainIcon;
  HICON hSmallIcon;

  // Load in our icon image
  //hMainIcon = LoadIcon(hInstance, "SysTrayDemo.ico");
  hMainIcon = (HICON)LoadImage(0, _T("resources/icon_large.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
  hSmallIcon = (HICON)LoadImage(0, _T("resources/icon_small.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

  // Check to make sure we loaded it
  if(!hMainIcon || !hSmallIcon) {
    std::cerr << "[error]: Unable to Load Icons" << std::endl;
  }

  // Create the main window class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName = "Copernicus";
  wcex.lpszClassName = "CopernicusMenu";
  wcex.hIcon = hMainIcon;
  wcex.hIconSm = hSmallIcon;

  // Return our constructed class
  return RegisterClassEx(&wcex);
}


//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  HWND hWnd;
  HICON hMainIcon;

  // Store instance handle in our global variable
  hInst = hInstance;

  // Create our windowIDM_ADMIN_PANEL
  hWnd = CreateWindow("CopernicusMenu", "CopernicusMenu", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, CW_USEDEFAULT, (HWND) NULL, (HMENU) NULL, hInstance, (LPVOID) NULL);

  // Check to make sure the window is created
  if (!hWnd) {
    return FALSE;
  }

  // Load in our icon image
  hMainIcon = (HICON)LoadImage(0, _T("resources/icon_large.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

  // Load the rest of the app settings
  nidApp.cbSize = sizeof(NOTIFYICONDATA); // sizeof the struct in bytes
  nidApp.hWnd = (HWND) hWnd; //handle of the window which will process this app. messages
  nidApp.uID = IDI_SYSTRAYDEMO; //ID of the icon that willl appear in the system tray
  nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; //ORing of all the flags
  nidApp.hIcon = hMainIcon; // handle of the Icon to be displayed, obtained from LoadIcon
  nidApp.uCallbackMessage = WM_USER_SHELLICON; 
  strcpy(nidApp.szTip, "Copernicus");
  Shell_NotifyIcon(NIM_ADD, &nidApp);

  // Success we have started the application
  return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT  - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  int wmId, wmEvent;
  POINT lpClickPoint;

  // Main switch, windows event types
  switch (message) {

  // System icon has been clicked
  case WM_USER_SHELLICON: 
    switch(LOWORD(lParam)) 
    {
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
        // Master flags for each button
        UINT uFlag = MF_BYPOSITION|MF_STRING;
        
        // Create the popup menu, which we will load buttons in
        HMENU hPopMenu = CreatePopupMenu();

        // Insert the about dialog
        InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION|MF_STRING, IDM_ADMIN_PANEL, _T("Admin Panel"));

        // Insert a nice separator
        InsertMenu(hPopMenu, 0xFFFFFFFF, MF_SEPARATOR, IDM_SEP, _T("SEP"));

        // If disabled is enabled, then grayout the test buttons
        if(!appCoper.is_enabled()) {
          uFlag |= MF_GRAYED;
        }

        // Add stats
        InsertMenu(hPopMenu, 0xFFFFFFFF, uFlag, IDM_STAT1, appCoper.get_dns_queries().c_str());
        InsertMenu(hPopMenu, 0xFFFFFFFF, uFlag, IDM_STAT2, appCoper.get_ads_blocked_total().c_str());
        InsertMenu(hPopMenu, 0xFFFFFFFF, uFlag, IDM_STAT3, appCoper.get_ads_blocked_percent().c_str());

        // Insert a nice separator
        InsertMenu(hPopMenu, 0xFFFFFFFF, MF_SEPARATOR, IDM_SEP, _T("SEP"));

        // If we are disabled, then show the enable button instead
        if(!appCoper.is_enabled()) {
          InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION|MF_STRING, IDM_ENABLE, _T("Enable"));
        }
        else {
          // Ping menu
          InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION|MF_STRING, IDM_PING, _T("Update"));
          // Disable meny
          InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION|MF_STRING, IDM_DISABLE, _T("Disable"));
        }   

        // Insert a nice separator
        InsertMenu(hPopMenu, 0xFFFFFFFF, MF_SEPARATOR, IDM_SEP, _T("SEP"));

        // Finally insert nice exit button for closing out
        InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION|MF_STRING, IDM_EXIT, _T("Exit"));

        // Display the menu, and put it near the cursor
        SetForegroundWindow(hWnd);
        GetCursorPos(&lpClickPoint);
        TrackPopupMenu(hPopMenu,TPM_RIGHTALIGN|TPM_LEFTBUTTON|TPM_BOTTOMALIGN,lpClickPoint.x,lpClickPoint.y,0,hWnd,NULL);
        return true;
    }
    break;

  // A button has been clicked
  case WM_COMMAND:
    // Get the id and event
    wmId = LOWORD(wParam);
    wmEvent = HIWORD(wParam);

    // Parse the menu selections:
    switch(wmId) {
      // Admin panel, open up the url
      case IDM_ADMIN_PANEL:
        ShellExecute(NULL, "open", appCoper.get_url().c_str(), NULL, NULL, SW_SHOWNORMAL);
        break;
      case IDM_PING:
        appCoper.update_stats();
        break;
      // Disable button have been clicked, toggle our state
      case IDM_DISABLE:
        appCoper.set_enabled(false);
        break;
      // Enable button has been clicked, toggle our state
      case IDM_ENABLE:
        appCoper.set_enabled(true);
        break;
      // Exit button, close the program, and destroy all parts
      case IDM_EXIT:
        Shell_NotifyIcon(NIM_DELETE,&nidApp);
        DestroyWindow(hWnd);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

  // Paint event
  //case WM_PAINT:
  //  hdc = BeginPaint(hWnd, &ps);
  //  // TODO: Add any drawing code here...
  //  EndPaint(hWnd, &ps);

  // Default exit if windows tells us to
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}


