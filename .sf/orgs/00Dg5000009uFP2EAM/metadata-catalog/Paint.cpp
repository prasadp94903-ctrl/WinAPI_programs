
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam)
{
    HDC hDc;
    PAINTSTRUCT ps;
    HPEN hPen;    // Declare without initializing
    HBRUSH hBrush;

    switch (msgid)
    {
    case WM_PAINT:
        hDc = BeginPaint(hWnd, &ps);

        // Set text color and background mode
        SetTextColor(hDc, RGB(0, 0, 255));  // Blue text
        SetBkMode(hDc, TRANSPARENT);

        // Draw text
        TextOut(hDc, 300, 300, L"Hello, Win32!", 14);

        // Initialize GDI objects (Fixed issue)
        hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        hBrush = CreateSolidBrush(RGB(255, 255, 0));

        // Select the pen and brush into the device context
        SelectObject(hDc, hPen);
        SelectObject(hDc, hBrush);

        // Draw a filled rectangle
        Rectangle(hDc, 100, 100, 300, 200);
        LineTo(hDc, 1000, 2000);
        

        // Cleanup GDI objects
        DeleteObject(hPen);
        DeleteObject(hBrush);

        EndPaint(hWnd, &ps);
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
    w.lpszClassName = L"SIVA";
    w.cbClsExtra = 0;  // Fixed NULL issue
    w.cbWndExtra = 0;  // Fixed NULL issue
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    w.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    w.lpfnWndProc = WndProc;
    w.lpszMenuName = NULL;
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
        TranslateMessage(&m);
        DispatchMessage(&m);
    }

    return (int)m.wParam;
}