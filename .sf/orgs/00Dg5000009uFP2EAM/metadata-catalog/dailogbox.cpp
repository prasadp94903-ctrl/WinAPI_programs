#include <Windows.h>

#if __has_include("resource.h")
#include "resource.h"
#else
#define IDR_MENU1 101
#define IDD_DIALOG1 102
#define ID_MODAL_WIN32MODAL 1001
#define ID_FILE_NEW 2001
#define ID_FILE_OPEN 2002
#define ID_NEW_CREATE 2003
#define ID_FILE_SAVE 2004
#define ID_FILE_SAVEAS 2005
#define ID_FILE_UNDO 2006
#define ID_FILE_READ 2007
#define ID_FILE_HELP 2008
#define ID_NEW_OPEN 2009
#define ID_CREATE_NEWPROJECT 2010
#define ID_DAILOGBOX_MODAL 2011
#define ID_DAILOGBOX_MODELESS 2012
#define ID_MODELESS_WIN32MODELES 2013
#endif

INT_PTR CALLBACK  ModalDlgProc(HWND hdlg, UINT msgid, WPARAM wParam, LPARAM lParam)
{
    switch (msgid)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            MessageBox(NULL, " OK BUTTON clicked", " OK", MB_OK | MB_ICONINFORMATION);
            EndDialog(hdlg, 0);
            break;
        case IDCANCEL:
            MessageBox(NULL, " CANCEL BUTTON clicked", " CANCEL", MB_OK | MB_ICONINFORMATION);
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
            MessageBox(hWnd, " File NEW", "New", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_OPEN:
            MessageBox(hWnd, " FIle open", "open ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_NEW_CREATE:
            MessageBox(hWnd, " new create", "create ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_SAVE:
            MessageBox(hWnd, " new save", "save ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_SAVEAS:
            MessageBox(hWnd, " Save as", "saveas ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_UNDO:
            MessageBox(hWnd, " file undo", "Undo ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_READ:
            MessageBox(hWnd, " newread", "read ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_FILE_HELP:
            MessageBox(hWnd, " new help", "help ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_NEW_OPEN:
            MessageBox(hWnd, " new open", "newopen ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_CREATE_NEWPROJECT:
            MessageBox(hWnd, " newproject", "NEWPROJECT ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_DAILOGBOX_MODAL:
            MessageBox(hWnd, " DAILOGBOX", "DAILOGBOX ", MB_OK | MB_ICONINFORMATION);
            break;
        case ID_DAILOGBOX_MODELESS:
            MessageBox(hWnd, " DAILOGBOXMODELES", "MODELES ", MB_OK | MB_ICONINFORMATION);
            break;
        
        case ID_MODELESS_WIN32MODELES:
            MessageBox(hWnd, " MODELES", "Modelsss ", MB_OK | MB_ICONINFORMATION);
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
        return DefWindowProc(hWnd, msgid, wParam, lParam);
    }
    return 0L;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX w = {};
    w.cbSize = sizeof(WNDCLASSEX);
    w.hInstance = hInstance;
    w.lpszClassName = "SIVA";
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
        MessageBox(NULL, "Window registration failed!", "ERROR", MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0, "SIVA", "HELLO", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,  // Fixed width & height
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, "Window creation failed!", "ERROR", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG m = {};
    while (GetMessage(&m, NULL, 0, 0))
    {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }

    return (int)m.wParam;
}
