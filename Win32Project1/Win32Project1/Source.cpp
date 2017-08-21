#include <windows.h>
#include "KWnd.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR Text[2000];
//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
nCmdShow)
{
   MSG msg;
    lstrcpy(Text,TEXT("Набраний текст:"));
   KWnd mainWnd (L"Hello Class Application", hInstance, nCmdShow, WndProc);
   while (GetMessage(&msg, NULL, 0, 0))  {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return msg.wParam;
}
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   HDC hDC;
   PAINTSTRUCT ps;
   RECT rect;

   
  
   int userReply;
   switch (uMsg)
   {
   case WM_PAINT:
      hDC = BeginPaint(hWnd, &ps);
      GetClientRect(hWnd, &rect);
      DrawText(hDC, Text, -1, &rect,
         DT_SINGLELINE | DT_CENTER | DT_VCENTER );
      EndPaint(hWnd, &ps);
      break;
   case WM_CLOSE:
      userReply = MessageBox(hWnd, L"Ви й справдi вирiшили покинути програму???",
         L"Вихід", MB_YESNO | MB_ICONQUESTION);
      if (IDYES == userReply)
         DestroyWindow(hWnd);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
	case WM_CHAR:
		   {
			   int len = lstrlen(Text);
      Text[len]=(wchar_t)wParam;
	  Text[len+1]=(wchar_t)'\0';
	  //MessageBox(hWnd,Text,L"yyy",0);
	  InvalidateRect(hWnd, NULL, TRUE);
	//SendMessage(hWnd,WM_PAINT,0,0);   
	  break;}
      
   default:
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
   return 0;
}



