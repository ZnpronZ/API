// EditBox.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "EditBox.h"

#define MAX_LOADSTRING 100
#define ID_EDIT 1
#define ID_LISTSV 2
#define ID_THEM 3

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwndEdit, hwndListBoxSV, btnThem;
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
    LoadStringW(hInstance, IDC_EDITBOX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITBOX));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITBOX));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EDITBOX);
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
    static int width, Height;
    static TCHAR hoten[30];
    switch (message)
    {
    case WM_CREATE:
        hwndEdit = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER,

            0, 0, 0, 0, hWnd, (HMENU)ID_EDIT, NULL, NULL);
        btnThem = CreateWindow(TEXT("button"), TEXT("Them"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            230, 20, 60, 50, hWnd, (HMENU)ID_THEM, NULL, NULL);
        hwndListBoxSV = CreateWindow(TEXT("listbox"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
            20, 80, 200, 300, hWnd, (HMENU)ID_LISTSV, NULL, NULL);
        SendMessage(hwndListBoxSV, LB_INSERTSTRING, 0, (LPARAM)TEXT("Nguyen Van An"));
        SendMessage(hwndListBoxSV, LB_INSERTSTRING, 1, (LPARAM)TEXT("Nguyen Thi Anh"));
        SendMessage(hwndListBoxSV, LB_INSERTSTRING, 2, (LPARAM)TEXT("Nguyen Van Hung"));
        SendMessage(hwndListBoxSV, LB_INSERTSTRING, 3, (LPARAM)TEXT("Tran Thi Huong"));
        SendMessage(hwndListBoxSV, LB_INSERTSTRING, 4, (LPARAM)TEXT("Nguyen Quoc Viet"));
        SetFocus(hwndEdit);
        break;
    case WM_SIZE:
        width = LOWORD(lParam);
        Height = HIWORD(lParam);
        MoveWindow(hwndEdit, 20, 20, 200, 50, TRUE);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_LISTSV:
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
                int index;
                if (MessageBox(NULL, TEXT("Ban co muon xoa sinh vien nay khong?"), TEXT("Hoi"),
                    MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                    index = SendMessage(hwndListBoxSV, LB_GETCURSEL, 0, 0);
                    SendMessage(hwndListBoxSV, LB_DELETESTRING, index, 0);
                }
                break;
            default:
                break;
            }
            break;
        case ID_THEM:
            int count;
            if (GetWindowTextLength(hwndEdit) == 0)
            {
                MessageBox(NULL, TEXT("Ban phai nhap ho ten"), TEXT(""), MB_OK);
                SetFocus(hwndEdit);
                return 0;
            }
            GetWindowText(hwndEdit, hoten, 30);
            count = SendMessage(hwndListBoxSV, LB_GETCOUNT, 0, 0);
            SendMessage(hwndListBoxSV, LB_INSERTSTRING, count, (LPARAM)hoten);
            SetWindowText(hwndEdit, TEXT(""));
            SetFocus(hwndEdit);
            break;
        case ID_EDIT:
            switch (HIWORD(wParam))
            {
            case   EN_CHANGE:
                if (GetWindowTextLength(hwndEdit) > 30)
                {


                    MessageBox(NULL, TEXT("Ban chi duoc doi da 30 kys tu"), TEXT(""), MB_OK);
                    SendMessage(hwndEdit, EM_SETSEL, 10, 11);
                    SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)TEXT(""));

                }

                break;
            default:
                break;
            }
            break;
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
