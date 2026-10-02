#include <Windows.h>

#if defined(__has_include)
#  if __has_include("resource.h")
#    include "resource.h"
#  else
#    define IDR_MENU1 100
#    define IDD_DIALOG1 101
#    define IDD_DIALOG2 102
#    define ID_MODAL_WIN32MODAL 40001
#    define ID_FILE_NEW 40002
#    define ID_FILE_OPEN 40003
#    define ID_NEW_CREATE 40004
#    define ID_FILE_SAVE 40005
#    define ID_FILE_SAVEAS 40006
#    define ID_FILE_UNDO 40007
#    define ID_FILE_READ 40008
#    define ID_FILE_HELP 40009
#    define ID_NEW_OPEN 40010
#    define ID_CREATE_NEWPROJECT 40011
#    define ID_DAILOGBOX_MODAL 40012
#    define ID_DAILOGBOX_MODELESS 40013
#    define ID_MODELESS_WIN32MODELES 40014
#  endif
#else
#  include "resource.h"
#endif

HWND hModelessDlg = NULL;
INT_PTR CALLBACK  ModelessDlgProc(HWND hdlg, UINT msgid, WPARAM wParam, LPARAM lParam)
{
    switch (msgid)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            MessageBox(NULL, L" OK BUTTON clicked", L" OK", MB_OK | MB_ICONINFORMATION);
            DestroyWindow(hdlg);
            hModelessDlg = NULL;
            break;
        case IDCANCEL:
            MessageBox(NULL, L" CANCEL BUTTON clicked", L" CANCEL", MB_OK | MB_ICONINFORMATION);
            DestroyWindow(hdlg);
            hModelessDlg = NULL;
            break;

        }
    case WM_CLOSE:
        DestroyWindow(hdlg);
        hModelessDlg = NULL;
        return TRUE;
    }

    return FALSE;
}

INT_PTR CALLBACK  ModalDlgProc(HWND hdlg, UINT msgid, WPARAM wParam, LPARAM lParam)
{
    switch (msgid)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            MessageBox(NULL, L" OK BUTTON clicked", L" OK", MB_OK | MB_ICONINFORMATION);
            EndDialog(hdlg, 0);
            break;
        case IDCANCEL:
            MessageBox(NULL, L" CANCEL BUTTON clicked", L" CANCEL", MB_OK | MB_ICONINFORMATION);
            EndDialog(hdlg, 0);
            break;

        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(hdlg);
        break;

    }
    return FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam)
{
    switch (msgid)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_MODAL_WIN32MODAL:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ModalDlgProc);
            break;
        case  ID_FILE_NEW:
            MessageBox(hWnd, L" File NEW", L"New", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_OPEN:
            MessageBox(hWnd, L" FIle open", L"open ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_NEW_CREATE:
            MessageBox(hWnd, L" new create", L"create ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_SAVE:
            MessageBox(hWnd, L" new save", L"save ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_SAVEAS:
            MessageBox(hWnd, L" Save as", L"saveas ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_UNDO:
            MessageBox(hWnd, L" file undo", L"Undo ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_READ:
            MessageBox(hWnd, L" newread", L"read ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_HELP:
            MessageBox(hWnd, L" new help", L"help ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_NEW_OPEN:
            MessageBox(hWnd, L" new open", L"newopen ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_CREATE_NEWPROJECT:
            MessageBox(hWnd, L" newproject", L"NEWPROJECT ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_DAILOGBOX_MODAL:
            MessageBox(hWnd, L" DAILOGBOX", L"DAILOGBOX ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_DAILOGBOX_MODELESS:
            MessageBox(hWnd, L" DAILOGBOXMODELES", L"MODELES ", MB_OK | MB_ICONINFORMATION);
            break;

        case ID_MODELESS_WIN32MODELES:
            if (!hModelessDlg) // Prevent multiple instances
                hModelessDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, ModelessDlgProc);
            ShowWindow(hModelessDlg, SW_SHOW);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    default:
        if (hModelessDlg && IsDialogMessage(hModelessDlg, (MSG*)&msgid))
            return TRUE;
        return DefWindowProc(hWnd, msgid, wParam, lParam);
    }
    return 0L;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX w = {};
    w.cbSize = sizeof(WNDCLASSEX);
    w.hInstance = hInstance;
    w.lpszClassName = L"SIVA";
    w.cbClsExtra = 0;  // Fixed NULL issue
    w.cbWndExtra = 0;  // Fixed NULL issue
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    w.lpfnWndProc = WndProc;
    w.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    w.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&w))
    {
        MessageBox(NULL, L"Window registration failed!", L"ERROR", MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0, L"SIVA", L"HELLO", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,  // Fixed width & height
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, L"Window creation failed!", L"ERROR", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG m = {};
    while (GetMessage(&m, NULL, 0, 0))
    {
        /*if (hModelessDlg && IsDialogMessage(hModelessDlg, &m)) 
            continue;*/ // continue poppup dialog box ok  or cancle buttons

        TranslateMessage(&m);
        DispatchMessage(&m);
    }

    return (int)m.wParam;
}
