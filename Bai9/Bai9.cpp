// Bai9.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bai9.h"

#define MAX_LOADSTRING 100
#define ID_ADD 1
#define ID_ADDALL 2
#define ID_DIS 3
#define ID_DISALL 4
#define ID_LISTSV_R 5
#define ID_LISTSV_L 6
#define ID_EXIT 7
#define ID_TB 8
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND btnAdd, hwndListBoxSVLeft, hwndListBoxSVRight,btnAddAll,btnDis,btnDisAll,btnExit;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BAI9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAI9));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAI9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAI9);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR monhoc[30];
    switch (message)
    {
    case WM_CREATE:

        hwndListBoxSVLeft = CreateWindow(TEXT("listbox"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
            20, 80, 200, 300, hWnd, (HMENU)ID_LISTSV_L, NULL, NULL);
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 0, (LPARAM)TEXT("Visual Basic"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 1, (LPARAM)TEXT("Văn phòng"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 2, (LPARAM)TEXT("Access"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 3, (LPARAM)TEXT("Pascal"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 4, (LPARAM)TEXT("Foxpro"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 5, (LPARAM)TEXT("Mạng"));
        SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 6, (LPARAM)TEXT("CTMT"));
        btnAdd = CreateWindow(TEXT("button"), TEXT(">"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 80, 60, 50, hWnd, (HMENU)ID_ADD, NULL, NULL);
        btnAddAll = CreateWindow(TEXT("button"), TEXT(">>"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 150, 60, 50, hWnd, (HMENU)ID_ADDALL, NULL, NULL);
        btnDis = CreateWindow(TEXT("button"), TEXT("<"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 220, 60, 50, hWnd, (HMENU)ID_DIS, NULL, NULL);
        btnDisAll = CreateWindow(TEXT("button"), TEXT("<<"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 290, 60, 50, hWnd, (HMENU)ID_DISALL, NULL, NULL);
        hwndListBoxSVRight = CreateWindow(TEXT("listbox"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
            320, 80, 200, 300, hWnd, (HMENU)ID_LISTSV_R, NULL, NULL);
        btnExit = CreateWindow(TEXT("button"), TEXT("Kết thúc"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 380, 100, 50, hWnd, (HMENU)ID_EXIT, NULL, NULL);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam),count;
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_ADD:
                
                SendMessage(hwndListBoxSVLeft, LB_GETTEXT, 0, (LPARAM)monhoc);
                count = SendMessage(hwndListBoxSVRight, LB_GETCOUNT, 0, 0);
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, count, (LPARAM)monhoc);
                SendMessage(hwndListBoxSVLeft, LB_DELETESTRING, 0, 0);
                break;
            case ID_ADDALL:
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 0, (LPARAM)TEXT("Visual Basic"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 1, (LPARAM)TEXT("Văn phòng"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 2, (LPARAM)TEXT("Access"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 3, (LPARAM)TEXT("Pascal"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 4, (LPARAM)TEXT("Foxpro"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 5, (LPARAM)TEXT("Mạng"));
                SendMessage(hwndListBoxSVRight, LB_INSERTSTRING, 6, (LPARAM)TEXT("CTMT"));
                SendMessage(hwndListBoxSVLeft, LB_RESETCONTENT, 0, 0);

                break;
            case ID_DIS:
                
                SendMessage(hwndListBoxSVRight, LB_GETTEXT, 0, (LPARAM)monhoc);
                count = SendMessage(hwndListBoxSVLeft, LB_GETCOUNT, 0, 0);
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, count, (LPARAM)monhoc);
                SendMessage(hwndListBoxSVRight, LB_DELETESTRING, 0, 0);
                break;
            case ID_DISALL:
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 0, (LPARAM)TEXT("Visual Basic"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 1, (LPARAM)TEXT("Văn phòng"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 2, (LPARAM)TEXT("Access"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 3, (LPARAM)TEXT("Pascal"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 4, (LPARAM)TEXT("Foxpro"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 5, (LPARAM)TEXT("Mạng"));
                SendMessage(hwndListBoxSVLeft, LB_INSERTSTRING, 6, (LPARAM)TEXT("CTMT"));
                SendMessage(hwndListBoxSVRight, LB_RESETCONTENT, 0, 0);

                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_EXIT:
                DestroyWindow(hWnd);
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
