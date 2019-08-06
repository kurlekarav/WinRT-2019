#include<Windows.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration 
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//MessageBox(NULL, TEXT("Application is started"), TEXT("Message"), MB_OK | MB_ICONINFORMATION);

	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;		//specialist
	HDC hCompatibleDC;
	BITMAP bitmap;
	PAINTSTRUCT PS;
	static HBITMAP hBitmap;
	RECT RC;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		HMODULE hModule;
		hModule = GetModuleHandleA(NULL);
		if(hModule == NULL)
			MessageBox(NULL, TEXT("GetModuleHandleA failed"), TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		hBitmap = LoadBitmap(hModule, MAKEINTRESOURCEA(MYBITMAP));
		if(hBitmap == NULL)
			MessageBox(NULL, TEXT("LoadBitmap failed"), TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PS);

		GetClientRect(hwnd, &RC);

		hCompatibleDC = CreateCompatibleDC(NULL);

		SelectObject(hCompatibleDC, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);

		//BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
		StretchBlt(hdc, RC.left, RC.top, RC.right, RC.bottom, hCompatibleDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		
		SelectObject(hCompatibleDC, hBitmap);
		
		DeleteDC(hCompatibleDC);
		
		DeleteObject(hCompatibleDC);
		
		EndPaint(hwnd, &PS);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}