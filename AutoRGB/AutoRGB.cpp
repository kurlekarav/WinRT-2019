#include<Windows.h>
#define MyTimer 101
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration 
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//initioalization od WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Applicatin"),
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
	HDC hdc;		//specialist
	PAINTSTRUCT PS;
	RECT RC;
	RECT RCTemp;
	static int iPaintFlag;
	HBRUSH HBrush;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		SetTimer(hwnd, MyTimer, 2000, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MyTimer);
		iPaintFlag++;
		if (iPaintFlag > 8)
		{
			iPaintFlag = 1;
		}
		SetTimer(hwnd, MyTimer, 2000, NULL);
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_PAINT:
		// get client area changing rectangle
		GetClientRect(hwnd, &RC);
		//call the specialist i.e create hdc
		hdc = BeginPaint(hwnd, &PS);
		RCTemp.top = RC.top;
		RCTemp.bottom = RC.bottom;
		RCTemp.left = RC.left;
		RCTemp.right = RC.right;
		if(iPaintFlag)
		{
			RCTemp.left = (iPaintFlag-1)*(RC.right/8);
			RCTemp.right = iPaintFlag*(RC.right/8);
		}
		
		switch(iPaintFlag)
		{
			case 1:
				HBrush = CreateSolidBrush(RGB(255,0,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;

			case 2:
				HBrush = CreateSolidBrush(RGB(0,255,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;

			case 3:
				HBrush = CreateSolidBrush(RGB(0,0,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;
				
			case 4:
				HBrush = CreateSolidBrush(RGB(0,255,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;				
				
			case 5:
				HBrush = CreateSolidBrush(RGB(255,0,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;

			case 6:
				HBrush = CreateSolidBrush(RGB(255,255,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;

			case 7:
				HBrush = CreateSolidBrush(RGB(0,0,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;

			case 8:
				HBrush = CreateSolidBrush(RGB(255,255,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RCTemp, HBrush);
				break;
		}
		EndPaint(hwnd, &PS);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}