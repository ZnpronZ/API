// Bai14.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bai14.h"

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
INT_PTR CALLBACK    dangky(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_BAI14, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BAI14));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BAI14));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BAI14);
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
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_DK:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, dangky);
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
INT_PTR CALLBACK dangky(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR maSV[9], hoten[30], khoa[30], KhoaHoc[3], monhoc[20], ketqua[60];
    static int count, indexKhoa, indexKhoaHoc, listCount;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_INSERTSTRING, -1, (LPARAM)TEXT("Công nghệ thông tin"));
        SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_INSERTSTRING, -1, (LPARAM)TEXT("Công trình"));
        SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_INSERTSTRING, -1, (LPARAM)TEXT("Kinh tế vận tải"));
        SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_INSERTSTRING, -1, (LPARAM)TEXT("55"));
        SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_INSERTSTRING, -1, (LPARAM)TEXT("56"));
        SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_INSERTSTRING, -1, (LPARAM)TEXT("57"));
        EnableWindow(GetDlgItem(hDlg, ID_DEL), FALSE);
        count = 0;
        return (INT_PTR)TRUE;
     

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_EXIT:

            if (MessageBox(NULL, TEXT("Bạn có muốn thoát không?"), TEXT("TB"), MB_YESNO | MB_ICONQUESTION) == IDYES)
                EndDialog(hDlg, TRUE);
            break;
        case ID_RESET:
            SetWindowText(GetDlgItem(hDlg, ID_SV), TEXT(""));
            SetWindowText(GetDlgItem(hDlg, ID_HOTEN), TEXT(""));
            SendMessage(GetDlgItem(hDlg, ID_THDC), BM_SETCHECK, 0, 0);
            SendMessage(GetDlgItem(hDlg, ID_GT), BM_SETCHECK, 0, 0);
            SendMessage(GetDlgItem(hDlg, ID_ENG), BM_SETCHECK, 0, 0);
            SendMessage(GetDlgItem(hDlg, ID_TH), BM_SETCHECK, 0, 0);
            SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_SETCURSEL, -1, 0);
            SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_SETCURSEL, -1, 0);
            count = 0;
            break;
        case ID_RES:
            wsprintf(ketqua, L"");
            wsprintf(monhoc, L"");
            //txtMaSV là ID của ô nhập mã SV
            if (GetWindowText(GetDlgItem(hDlg, ID_SV), maSV, 9) != 8)
            {
                MessageBox(NULL, TEXT("Bạn phải nhập mã SV là chuỗi gồm 8 ký tự"), TEXT(""), MB_OK);
                SetFocus(GetDlgItem(hDlg, ID_SV));
                return 0;
            }
            if (GetWindowText(GetDlgItem(hDlg, ID_HOTEN), hoten, 30) == 0)
            {
                MessageBox(NULL, TEXT("Bạn phải nhập họ tên SV"), TEXT(""), MB_OK);
                SetFocus(GetDlgItem(hDlg, ID_HOTEN));
                return 0;
            }
            indexKhoa = SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_GETCURSEL, 0, 0);
            if (indexKhoa < 0)
            {
                MessageBox(NULL, TEXT("Bạn phải chọn Khoa"), TEXT(""), MB_OK);

            }

            else
                SendMessage(GetDlgItem(hDlg, ID_KHOAS), CB_GETLBTEXT, indexKhoa, (LPARAM)khoa);
            indexKhoaHoc = SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_GETCURSEL, 0, 0);
            if (indexKhoaHoc < 0)
            {
                MessageBox(NULL, TEXT("Bạn phải chọn Khóa học"), TEXT(""), MB_OK);

            }

            else
                SendMessage(GetDlgItem(hDlg, ID_KHOA), CB_GETLBTEXT, indexKhoaHoc, (LPARAM)KhoaHoc);
            if (SendMessage(GetDlgItem(hDlg, ID_THDC), BM_GETCHECK, 0, 0) == TRUE)
            {
                count++;
                wsprintfW(monhoc, L"%s;Tin học đại cương", monhoc);
            }
            if (SendMessage(GetDlgItem(hDlg, ID_GT), BM_GETCHECK, 0, 0) == TRUE)
            {
                count++;
                wsprintfW(monhoc, L"%s;Giải tích F1", monhoc);
            }
            if (SendMessage(GetDlgItem(hDlg, ID_ENG), BM_GETCHECK, 0, 0) == TRUE)
            {
                count++;
                wsprintfW(monhoc, L"%s;Tiếng anh A1", monhoc);
            }
            if (SendMessage(GetDlgItem(hDlg, ID_TH), BM_GETCHECK, 0, 0) == TRUE)
            {
                count++;
                wsprintfW(monhoc, L"%s;Triết học F1", monhoc);
            }
            if (count < 2)
            {
                MessageBox(NULL, TEXT("Bạn phải đăng ký ít nhất hai môn"), TEXT("Hi"), MB_OK);
                return 0;
            }
            listCount = SendMessage(GetDlgItem(hDlg, ID_LISTDK), LB_GETCOUNT, 0, 0);
            wsprintfW(ketqua, L"%d.%s|%s|%s|%s|%s", (listCount + 1), maSV, hoten, khoa, KhoaHoc, monhoc);

            SendMessage(GetDlgItem(hDlg, ID_LISTDK), LB_INSERTSTRING, -1, (LPARAM)ketqua);
            break;

        default:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    break;
    }
    return (INT_PTR)FALSE;
}