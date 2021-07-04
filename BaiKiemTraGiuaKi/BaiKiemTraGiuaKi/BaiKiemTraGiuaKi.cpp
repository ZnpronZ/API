// BaiKiemTraGiuaKi.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "BaiKiemTraGiuaKi.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_BAIKIEMTRAGIUAKI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAIKIEMTRAGIUAKI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAIKIEMTRAGIUAKI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAIKIEMTRAGIUAKI);
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
    static int xLeft, xRight, yTop, yBottom;
    static int Hinh;//hình mình chọn
    static HBRUSH hBrushHinh;//màu nền
    static HPEN hPen;//viền chọn
    static POINT point[3];
    static HDC hdc;
    static int n = 0, i, j, m = 50, s = 0, x, y;
    static TCHAR timeLeft[30];
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 1000, NULL);
        break;
    case WM_SIZE:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_TIMER:
        //Nếu 0<s<=59--> s=s-1, m giữ nguyên
        if (s > 0 && s <= 59)
        {
            s = s - 1;
        }
        else
        {
            if (s == 0 && m > 0) //Nếu s=0 thì m=m-1; s=59
            {
                s = 59;
                m = m - 1;
            }
        }
        //Ghi ra chửa số giá trị đếm được
        wsprintf(timeLeft, L"Time left: %d:%d", m, s);
        hdc = GetDC(hWnd);
        TextOut(hdc, x - 120, y - 30, timeLeft, 30);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_COMMAND:
        {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
            //chọn id của hình và gắn vào biến Hình
        case ID_ELIP:
            hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
            Hinh = ID_ELIP;
            break;
        case ID_TAMGIAC:
            hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
            Hinh = ID_TAMGIAC;
            break;
            //chọn id nền và gắn vào biến
        case ID_NENVANG:
            hBrushHinh = CreateSolidBrush(RGB(225, 225, 0));
            break;
        case ID_NENXANH:
            hBrushHinh = CreateSolidBrush(RGB(0, 255, 0));
            break;
            //chọn id viền và gắn vào biến
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            if (MessageBox(hWnd, L"Bạn có muốn thoát không?", L"Thông Báo", MB_OKCANCEL) == IDOK)
                DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        break;

    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);
        hdc = GetDC(hWnd);
        SelectObject(hdc, hPen);
        SelectObject(hdc, hBrushHinh);
        if (Hinh == ID_ELIP)
            Ellipse(hdc, xLeft, yTop, xRight, yBottom);
        if (Hinh == ID_TAMGIAC)
        {
            point[0].x = xLeft + (xRight - xLeft) / 2;
            point[0].y = yTop;

            point[1].x = xLeft;
            point[1].y = yBottom;

            point[2].x = xRight;
            point[2].y = yBottom;

            Polygon(hdc, point, 3);

        }
        ReleaseDC(hWnd, hdc);
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
