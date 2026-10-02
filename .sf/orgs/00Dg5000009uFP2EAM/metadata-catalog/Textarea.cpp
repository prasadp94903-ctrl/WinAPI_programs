#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
    switch (msgId)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;
    default:
        return DefWindowProc(hWnd, msgId, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEX w = {};
    w.cbSize = sizeof(WNDCLASSEX);
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hCursor = LoadCursor(nullptr, IDC_ARROW);
    w.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    w.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    w.lpszClassName = "SIVA";
    w.lpszMenuName = nullptr;

    if (!RegisterClassEx(&w))
    {
        MessageBox(nullptr, "Window registration failed", "ERROR", MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0,
        "SIVA",
        "HELLO",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        MessageBox(nullptr, "Window creation failed", "ERROR", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}