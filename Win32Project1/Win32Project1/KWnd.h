#pragma once
#include<Windows.h>
class KWnd
{
public:
     KWnd(LPCTSTR windowName, HINSTANCE hInst, int cmdShow,
      LRESULT (WINAPI *pWndProc)(HWND,UINT,WPARAM,LPARAM),
      LPCTSTR menuName = NULL,
      int x = CW_USEDEFAULT, int y = 0,
      int width = CW_USEDEFAULT, int height = 0,
      UINT classStyle =  CS_HREDRAW | CS_VREDRAW,
      DWORD windowStyle = WS_OVERLAPPEDWINDOW | WS_ACTIVECAPTION,
      HWND hParent = NULL);
     HWND GetHWnd() { return hWnd; }
protected:
   HWND hWnd;
   WNDCLASSEX wc;
};
