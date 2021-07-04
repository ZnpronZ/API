// GDI_EXamp.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Menu_va_tai_nguyen.h"

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
    LoadStringW(hInstance, IDC_MENUVATAINGUYEN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MENUVATAINGUYEN));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MENUVATAINGUYEN));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    static HDC hdc;
    static int x, y, xoa = 0, hinh, xleft, ytop, xright, ybottom;
    static POINT point[3];
    static HPEN hPenYellow,hPenRed;
    static HBRUSH hBrushGreen,hBrushBlue,hBrushStyle;

    switch (message)
    {
    case WM_SIZE:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_LBUTTONDOWN:
        xleft = LOWORD(lParam);
        ytop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xright = LOWORD(lParam);
        ybottom = HIWORD(lParam);
        hdc = GetDC(hWnd);
        if (hinh == ID_TOOL_HCN)
            Rectangle(hdc, xleft, ytop, xright, ybottom);
        if (hinh == ID_TOOL_ESCLIP)
            Ellipse(hdc, xleft, ytop, xright, ybottom);
        if (hinh == ID_TOOL_TGC)
        {

            point[0].x = xleft + (xright - xleft) / 2;
            point[0].y = ytop;
            point[1].x = xleft;
            point[1].y = ybottom;
            point[2].x = xright;
            point[2].y = ybottom;
            Polygon(hdc, point, 3);

        }
        ReleaseDC(hWnd, hdc);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {

        case ID_TOOL_TGC:
            hinh = ID_TOOL_TGC;
            break;
        case ID_TOOL_ESCLIP:
            hinh = ID_TOOL_ESCLIP;
            break;
        case ID_TOOL_HCN:
            hinh = ID_TOOL_HCN;
            break;
        case ID_TOOL_DELETE:
            xoa = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        /*case ID_FILE_CREATELINE:
            hdc = GetDC(hWnd);
            for (int i = 50; i <= 100; i++)
                SetPixel(hdc, i, 50, RGB(255, 0, 0));
            MoveToEx(hdc, 100, 50, NULL);
            LineTo(hdc, 100, 100);
            ReleaseDC(hWnd, hdc);
            break;*/
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case ID_TOOL_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        if (xoa == 0)
        {
            hPenRed = CreatePen(PS_SOLID,2, RGB(255,0, 0));
            hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
            hBrushBlue = CreateSolidBrush(RGB(0, 255, 255));
            hBrushStyle = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 255));
            SelectObject(hdc, hBrushGreen);
            Rectangle(hdc, x / 8, y / 8, 7 * x / 8, 7 * y / 8);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, x, y);
            MoveToEx(hdc, x, 0, NULL);
            LineTo(hdc, 0, y);
            SelectObject(hdc, hPenRed);
            SelectObject(hdc, hBrushStyle);
            hPenYellow = CreatePen(PS_DASH, 5, RGB(255, 255, 0));

            Ellipse(hdc, x / 8, y / 8, 7 * x / 8, 7 * y / 8);
            SelectObject(hdc, hPenYellow);
            SelectObject(hdc, hBrushBlue);
            RoundRect(hdc, x / 4, y / 4, 3 * x / 4, 3 * y / 4, 100, 100);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(hPenYellow);
        DeleteObject(hPenRed);
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
