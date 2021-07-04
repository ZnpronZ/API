// Bai8.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bai8.h"
#include "stdio.h"
#define MAX_LOADSTRING 100
#define ID_EDIT 1
HWND hwndEdit;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL FileWrite(HWND hwndEdit, PSTR StringFileName);
BOOL FileOpen(HWND hwndEdit, PSTR StringFileName);
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
    LoadStringW(hInstance, IDC_BAI8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAI8));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAI8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAI8);
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
    switch (message)
    {
        static int x, y;
    case WM_CREATE:
        hwndEdit = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
            WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
            0, 0, 0, 0, hWnd, (HMENU)ID_EDIT, NULL, NULL);
        break;
    case WM_SIZE:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        MoveWindow(hwndEdit, 0, 0, x, y, TRUE);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_EDIT_COPY:
                SendMessage(hwndEdit, WM_COPY, 0, 0);
                break;
            case ID_EDIT_CUT:
                SendMessage(hwndEdit, WM_CUT, 0, 0);
                break;
            case ID_EDIT_PASTE:
                SendMessage(hwndEdit, WM_PASTE, 0, 0);
                break;
            case ID_FILE_NEW:
                SetWindowText(hwndEdit, TEXT(""));
                break;
            case ID_FILE_SAVE:
                if (!FileWrite(hwndEdit, (PSTR)"TestWrite.txt"))
                    MessageBox(NULL, TEXT("Lưu file không thành công"), TEXT("Thông báo"), MB_OK | MB_ICONWARNING);
                else
                {
                    MessageBox(NULL, TEXT("Lưu file thành công!"), TEXT("Thông báo"), MB_OK | MB_ICONINFORMATION);
                }
                break;
            case ID_FILE_OPEN:
                if (!FileOpen(hwndEdit, (PSTR)"TestWrite.txt"))
                    MessageBox(NULL, TEXT("Lưu file không thành công"), TEXT("Thông báo"), MB_OK | MB_ICONWARNING);
                else
                {
                    MessageBox(NULL, TEXT("Lưu file thành công!"), TEXT("Thông báo"), MB_OK | MB_ICONINFORMATION);
                }
                break;
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
BOOL FileWrite(HWND hwndEdit, PSTR StringFileName)
{
    FILE* pFile;
    PSTR pstrBuffer;
    long iLength;
    fopen_s(&pFile, StringFileName, "wb");
    if (!pFile)
    {

        return FALSE;
    }
    iLength = GetWindowTextLength(hwndEdit);
    pstrBuffer = (PSTR)malloc(iLength + 1);
    if (pstrBuffer == NULL)
    {
        fclose(pFile);
        return FALSE;
    }
    GetWindowText(hwndEdit, (LPWSTR)pstrBuffer, iLength + 1);
    if (iLength != (int)fwrite(pstrBuffer, 1, 2 * iLength, pFile))
    {
        fclose(pFile);
        return FALSE;
    }
    fclose(pFile);

    return TRUE;
}
BOOL FileOpen(HWND hwndEdit, PSTR StringFileName)
{
    FILE* pFile;
    PSTR pstrBuffer;
    long iLength;
    fopen_s(&pFile, StringFileName, "rb");
    if (!pFile)
    {

        return FALSE;
    }
    char c, r[100];
    int i = 0;
    while ((c = getc(pFile)) != EOF)
    {
        r[i++] = c;
        i++;
    }
    pstrBuffer = (PSTR)malloc(i+ 1);
   
    if (pstrBuffer == NULL)
    {
        fclose(pFile);
        return FALSE;
    }
    SetWindowText(hwndEdit, (LPWSTR)r);

    fclose(pFile);

    return TRUE;
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
