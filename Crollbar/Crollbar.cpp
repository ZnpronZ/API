// Crollbar.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Crollbar.h"

#define MAX_LOADSTRING 100


// Global Variables:
HWND vsCroll[3], stColor[3], valueColor[3];
RECT rectColor;
HINSTANCE hInst;
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
    LoadStringW(hInstance, IDC_CROLLBAR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CROLLBAR));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROLLBAR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CROLLBAR);
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
        CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
    static TCHAR szBuffer[10], labelcolor[3][6] = { TEXT("Red"),TEXT("Green"),TEXT("Blue") };
    static int color[3];
    static int i;
    static COLORREF crPrim[3] = { RGB(255, 0, 0), RGB(0, 255, 0),
                                   RGB(0, 0, 255) };
    static HBRUSH  hBrush[3], hBrushStatic;
    switch (message)
    {
    case WM_CREATE:
        int i;
        int x, y;
        x = 20; y = 20;
        for (i = 0; i < 3; i++)
        {
            stColor[i] = CreateWindow(TEXT("static"), labelcolor[i], WS_CHILD | WS_VISIBLE, x + i * 60 + 3, y, 60, 30, hWnd,
                (HMENU)i + 3, NULL, NULL);
            vsCroll[i] = CreateWindow(TEXT("scrollBar"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT, x + i * 60 + 3, y + 35, 40, 200, hWnd,
                (HMENU)i, NULL, NULL);
            SetScrollRange(vsCroll[i], SB_CTL, 0, 255, TRUE);
            SetScrollPos(vsCroll[i], SB_CTL, 0, FALSE);

            valueColor[i] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE, x + i * 60 + 3, y + 240, 60, 30, hWnd,
                (HMENU)i + 6, NULL, NULL);
            SetRect(&rectColor, 230, 20, 500, 550);
            hBrush[i] = CreateSolidBrush(crPrim[i]);

        }
        hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
        break;

    case WM_CTLCOLORSCROLLBAR: //Thay doi mau cho crollBar
        i = GetWindowLong((HWND)lParam, GWL_ID);
        return (LRESULT)hBrush[i];

    case WM_CTLCOLORSTATIC: //Thay doi mau cho Static
        i = GetWindowLong((HWND)lParam, GWL_ID);
        SetTextColor((HDC)wParam, crPrim[i % 3]);
        return (LRESULT)hBrushStatic;
        break;

    case WM_VSCROLL:
        i = GetWindowLong((HWND)lParam, GWL_ID);

        switch (LOWORD(wParam))
        {
        case SB_PAGEDOWN:
            color[i] += 15;
            break;
        case SB_LINEDOWN:
            color[i] = min(255, color[i] + 1);
            break;

        case SB_PAGEUP:
            color[i] -= 15;
            break;
            // fall through
        case SB_LINEUP:
            color[i] = max(0, color[i] - 1);
            break;

        case SB_TOP:
            color[i] = 0;
            break;

        case SB_BOTTOM:
            color[i] = 255;
            break;

        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            color[i] = HIWORD(wParam);
            break;

        default:
            break;
        }
        SetScrollPos(vsCroll[i], SB_CTL, color[i], TRUE);
        wsprintf(szBuffer, L"%i", color[i]);
        SetWindowText(valueColor[i], szBuffer);
        DeleteObject((HBRUSH)
            SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)
                CreateSolidBrush(RGB(color[0], color[1], color[2]))));

        InvalidateRect(hWnd, &rectColor, TRUE);
        return 0;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
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
