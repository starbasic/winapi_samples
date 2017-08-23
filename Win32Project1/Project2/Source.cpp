#include <windows.h> 
//#include <tchar.h> 
#include <string>
 using namespace std;
//�������� ������ ��������� 
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM); 
HWND hStop;
HINSTANCE gHinst;
 
TCHAR szClassWindow[] = TEXT("��������� ����������");  /* ��� ����� ���� */ 
 
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, 
int nCmdShow) 
{ 
  HWND hWnd; 
  MSG lpMsg; 
  WNDCLASSEX wcl; 
 
  /* 1. ���� �������� ����� ����  */ 
 
  wcl.cbSize = sizeof (wcl);  // ����� ��������� WNDCLASSEX  
  wcl.style = CS_HREDRAW | CS_VREDRAW; // CS(Class Style) - ����� ������  ���� 
  wcl.lpfnWndProc = WindowProc; // ����� ������� ��������� 
  wcl.cbClsExtra = 0;  // ����������� Windows  
  wcl.cbWndExtra  = 0;   // ����������� Windows  
  wcl.hInstance = hInst;  // ���������� ��������
  // �������� ���������� ������ 
  wcl.hIcon = LoadIcon(NULL, IDI_ASTERISK); 
  // �������� ������������ ������� 
  wcl.hCursor = LoadCursor(NULL, IDC_SIZEALL); 
  wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);   
  wcl.lpszMenuName = NULL;  //������� �� �� ���� 
  wcl.lpszClassName = szClassWindow;  //��� ������ ���� 
  wcl.hIconSm = NULL; // ���������� ��������� ������ 
   
  /*  2. ��������� ����� ����  */ 
 
  if (!RegisterClassEx(&wcl)) 
    return 0; 
 
  /*  3. ��������� ����  */ 
 
  hWnd = CreateWindowEx( 
    WS_EX_WINDOWEDGE,    // ����������� ����� ����
	   szClassWindow,  // ��'� ����� ���� 
    TEXT("�������� ����������"), // ��������� ���� 
    WS_OVERLAPPEDWINDOW|WS_HSCROLL,  // ����� ���� 
    CW_USEDEFAULT,  // �-���������� ����� ��������� ���� ���� 
    CW_USEDEFAULT,  // y-���������� ����� ��������� ���� ���� 
    CW_USEDEFAULT,  // ������ ���� 
    CW_USEDEFAULT,  // ������ ���� 
    NULL,     // ���������� ������������ ���� 
    NULL,     // ���������� ���� ���� 
    hInst,    // ���������� �������, �� ������� ���� 
    NULL);    // �������� �� ������� ������ ������� 
   
  /* 4. ³���������� ���� */ 
 
  ShowWindow(hWnd, SW_NORMAL); 
  UpdateWindow(hWnd);

  gHinst = hInst;
 
  /* 5. ���� ������� ����������  */ 
 
  while(GetMessage(&lpMsg, NULL, 0, 0))  
  { 
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);  
  } 
  return lpMsg.wParam; 
}   


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   HDC hDC;
   PAINTSTRUCT ps;
    TEXTMETRIC tm;
   static string text; // ����� ��� ��������� ������
   string symb;
   static int cxChar, cyChar, cxClient, cyClient;
   static int nCharPerLine, nClientLines;
   static int xCaret = 0, yCaret = 0;
   int curIndex;
   int nLines; // �-��� ����� ������
   int nTailChar; // �-��� ������� � ������� ������
   int x, y, i;
   switch (uMsg) {
   case WM_CREATE:
      hDC = GetDC(hWnd);
      SelectObject(hDC, GetStockObject(SYSTEM_FIXED_FONT));
      GetTextMetrics(hDC, &tm);
      cxChar = tm.tmAveCharWidth;
      cyChar = tm.tmHeight;
      ReleaseDC(hWnd, hDC);
      break;
   case WM_SIZE:
      // �������� ������ ���� � ��������
      cxClient = LOWORD(lParam);
      cyClient = HIWORD(lParam);
      //��������� ������ ���� � �������� 
      nCharPerLine = max(1, cxClient / cxChar);
      nClientLines = max(1, cyClient / cyChar);
      if (hWnd == GetFocus())
         SetCaretPos(xCaret * cxChar, yCaret * cyChar);
      break;
   case WM_SETFOCUS:
      // �������� � ��������
      CreateCaret(hWnd, NULL, 0, cyChar);
      SetCaretPos(xCaret * cxChar, yCaret * cyChar);
      ShowCaret(hWnd);
      break;
   case WM_KILLFOCUS:
      // ������� � �������
      HideCaret(hWnd);
      DestroyCaret();
      break;
   case WM_KEYDOWN:
      nLines = text.size() / nCharPerLine;
      nTailChar = text.size() % nCharPerLine;
      switch (wParam) {
      case VK_HOME:   xCaret = 0;
                      break;
		case VK_END:    if (yCaret == nLines)
                         xCaret = nTailChar;
                      else
                         xCaret = nCharPerLine - 1;
                      break;
      case VK_PRIOR:  yCaret = 0;
                      break;
      case VK_NEXT:   yCaret = nLines;
                      xCaret = nTailChar;
                      break;
      case VK_LEFT:   xCaret = max(xCaret - 1, 0);
                      break;
      case VK_RIGHT:  xCaret = min(xCaret + 1, nCharPerLine - 1);
                      if ((yCaret == nLines) && (xCaret > nTailChar))
                         xCaret = nTailChar;
                      break;
      case VK_UP:     yCaret = max(yCaret - 1, 0);
                      break;
      case VK_DOWN:   yCaret = min(yCaret + 1, nLines);
                      if ((yCaret == nLines) && (xCaret > nTailChar))
                         xCaret = nTailChar;
                      break;
      case VK_DELETE: curIndex = yCaret * nCharPerLine + xCaret;
                      if (curIndex < text.size()) {
                         text.erase(curIndex, 1);
                         InvalidateRect(hWnd, NULL, TRUE);
                      }
                      break;
      }
      SetCaretPos(xCaret * cxChar, yCaret * cyChar);
      break;
   case WM_CHAR:
      switch (wParam) {
      case '\b':  // ������ 'backspace'
         if (xCaret > 0) {
            xCaret--;
            SendMessage(hWnd, WM_KEYDOWN, VK_DELETE, 1);
         }
         break;
      case '\t':  // ������ 'tab'
         do { SendMessage(hWnd, WM_CHAR, ' ', 1L); }
         while (xCaret % 8 != 0);
         break;
      case '\r': case '\n':  // ���������� ������� 
         for (i = 0; i < nCharPerLine - xCaret; ++i)
            text += ' ';
         xCaret = 0;
         if (++yCaret == nClientLines) {
            MessageBox(hWnd, "��� ����� � ����", "Error", MB_OK);
            yCaret--;
         }
  break;
      default: // ���� �������
         curIndex = yCaret * nCharPerLine + xCaret;
         if (curIndex == text.size())
            text += (char)wParam;
         else {
            symb = (char)wParam;
            text.insert(curIndex, symb);
         }
         InvalidateRect(hWnd, NULL, TRUE);
         if (++xCaret == nCharPerLine) {
            xCaret = 0;
            if (++yCaret == nClientLines) {
               MessageBox(hWnd, "��� ����� � ����", "Error", MB_OK);
               yCaret--;
            }
         }
         break;
      }
      SetCaretPos(xCaret * cxChar, yCaret * cyChar);
      break;
   case WM_PAINT:
      hDC = BeginPaint(hWnd, &ps);
      SelectObject(hDC, GetStockObject(SYSTEM_FIXED_FONT));
      if (text.size()) {
         nLines = text.size() / nCharPerLine;
         nTailChar = text.size() % nCharPerLine;
         for (y = 0; y < nLines; ++y)
            TextOut(hDC, 0, y*cyChar, text.c_str() + y*nCharPerLine,
               nCharPerLine);
         TextOut(hDC, 0, y*cyChar, text.c_str() + y*nCharPerLine,
            nTailChar);
      }
      EndPaint(hWnd, &ps);
      break;
   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   default:
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
   return 0;
}

