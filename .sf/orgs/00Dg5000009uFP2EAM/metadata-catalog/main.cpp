#include<Windows.h>
LRESULT CALLBACK WNDProc(HWND hWnd, UINT msgid, WPARAM wParam, LPARAM lParam)
{
	switch (msgid)
	{
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
WNDCLASS w;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	w.lpszClassName = "My Window";
	w.lpfnWndProc = WNDProc;
	w.hInstance = hInstance;
	w.lpszMenuName = "My class";
	RegisterClass(&w);
	HWND hWnd = CreateWindow("My Window", "My class", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}