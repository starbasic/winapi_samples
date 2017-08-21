#include "KWnd.h"
#include "resource.h"


KWnd::KWnd(LPCTSTR windowName, HINSTANCE hInst, int cmdShow,
               LRESULT (WINAPI *pWndProc)(HWND,UINT,WPARAM,LPARAM),
               LPCTSTR menuName, int x, int y, int width, int height,
               UINT classStyle, DWORD windowStyle, HWND hParent)
{
   wchar_t szClassName[] = L"KWndClass";
   wc.cbSize        = sizeof(wc);
   wc.style         = classStyle;
   wc.lpfnWndProc   = pWndProc;
   wc.cbClsExtra    = 0;
   wc.cbWndExtra    = 0;
   wc.hInstance     = hInst;
   wc.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
   wc.hCursor       = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
   wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wc.lpszMenuName  = menuName;
   wc.lpszClassName = szClassName;
   wc.hIconSm       = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
   // Регистрируем класс окна
   if (!RegisterClassEx(&wc)) {
      wchar_t msg[100] = L"Cannot register class: ";
      wcscat(msg, szClassName);
      MessageBox(NULL, msg, TEXT("Error"), MB_OK);
      return;
   }
   // Создаем окно
   hWnd = CreateWindow(szClassName, windowName, windowStyle,
      x, y, width, height, hParent, (HMENU)NULL, hInst, NULL);
   if (!hWnd) {
      TCHAR text[100] = TEXT("Cannot create window: ");
      lstrcat(text, windowName);
      MessageBox(NULL, text, TEXT("Error"), MB_OK);
      return;
        }
   // Показываем  окно
   ShowWindow(hWnd, cmdShow);
}
