// Bai5.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bai5.h"

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
INT_PTR CALLBACK    QLSV(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_BAI5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAI5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAI5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAI5);
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            
            case ID_DMSV:
                DialogBox(hInst, MAKEINTRESOURCE(DLG_SV), hWnd, QLSV);
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
INT_PTR CALLBACK QLSV(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int count, listCount, indexSP, index, lenght;
    static TCHAR ketqua[300], Name[30], temp[30];
    static TCHAR input[30]; 
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING, 0, (LPARAM)TEXT("Nguyên Van A"));
        SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING, 1, (LPARAM)TEXT("Nguyên Van B"));
        SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING, 2, (LPARAM)TEXT("Nguyên Van C"));
        SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING, 3, (LPARAM)TEXT("Nguyên Van D"));
        return (INT_PTR)TRUE;
    case WM_CREATE:
        
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_TIMKIEM:
            lenght = GetWindowText(GetDlgItem(hDlg, ID_TXTHOTEN), input, 30);
            if (lenght == 0) {
                MessageBox(NULL, TEXT("Bạn Phải Nhập thông tin cần tìm"), TEXT("OK"), MB_OK | MB_ICONWARNING);
                SetFocus(GetDlgItem(hDlg, ID_TXTHOTEN));
            }
            else {
                count = SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_GETCOUNT, 0, 0);
                for (int i = 0; i < count; i++) {
                    SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_GETTEXT, i, (LPARAM)temp);
                    if (lstrcmp(input, temp) == 0) {
                        MessageBox(NULL, TEXT("Tìm Thấy"), TEXT("OK"), MB_OK);
                        SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_SETCURSEL, i, 0);
                        break;
                    }
                    else
                    {
                        MessageBox(NULL, TEXT("Không Tìm Thấy"), TEXT("OK"), MB_OK);
                    }
                    break;
                }
            }
            break;
        case ID_SUA:
            index = SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_GETCURSEL, 0, 0);
            GetWindowText(GetDlgItem(hDlg, ID_TXTHOTEN), input, 30);
            SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_DELETESTRING, index, 0);
            SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING, index, (LPARAM)input);
            break;
        case ID_THOAT:
            if (MessageBox(NULL, TEXT("Bạn có muốn thoát không ?"), TEXT("Thông Báo"), MB_YESNO | MB_ICONQUESTION) == IDYES)
                EndDialog(hDlg, TRUE);
            break;
        case ID_THEM:
            lenght = GetWindowText(GetDlgItem(hDlg, ID_TXTHOTEN), Name, 30);
            if (lenght == 0)
            {
                MessageBox(NULL, TEXT("Bạn chưa nhập họ tên "), TEXT("Thông Báo"), MB_OK | MB_ICONINFORMATION);
                SetFocus(GetDlgItem(hDlg, ID_TXTHOTEN));
            }
            else
            {
                count = SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_GETCOUNT, 0, 0);
                SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_INSERTSTRING,count, (LPARAM)Name);
                SetWindowText(GetDlgItem(hDlg, ID_TXTHOTEN), TEXT(""));
                SetFocus(GetDlgItem(hDlg, ID_TXTHOTEN));
            }
            break;
        case ID_XOA:
            index = SendMessage(GetDlgItem(hDlg, ID_LISTSV),LB_GETCURSEL,0,0);
            if (index < 0)
            {
                MessageBox(NULL, TEXT("Bạn phải chọn một phần tử để xóa"), TEXT("Thông báo"), MB_OK | MB_ICONINFORMATION);

            }
            else
            {
                if (MessageBox(NULL, TEXT("Bạn có muốn xóa không "), TEXT("Thông báo"), MB_YESNO | MB_ICONQUESTION) == IDYES);
                SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_DELETESTRING, index, 0);

            }
            break;
        case ID_LISTSV:
            // db click event for delete
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
                if (MessageBox(NULL, TEXT("Bạn thật sự muốn xóa không"), TEXT(""), MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                    SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_DELETESTRING, index, 0);
                }
                break;
            default:
                break;
            }
            index = SendMessage(GetDlgItem(hDlg, ID_LISTSV), LB_GETCURSEL, 0, 0);
            SendMessage(GetDlgItem(hDlg, ID_LISTSV ), LB_GETTEXT, index, (LPARAM)input);
            SetWindowText(GetDlgItem(hDlg, ID_TXTHOTEN), input);
            break;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
