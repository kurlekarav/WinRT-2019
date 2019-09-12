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
		1200,
		500,
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
	HFONT hFont,hTmp;
	TCHAR str1[255], str2[255], str3[255], str4[255], str5[255], str6[255];

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

		hFont=CreateFont(40,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,"SYSTEM_FIXED_FONT");
		hTmp=(HFONT)SelectObject(hdc,hFont);
		GetTextAlign(hdc);
		//BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
		StretchBlt(hdc, RC.left, RC.top, RC.right, RC.bottom, hCompatibleDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		SelectObject(hCompatibleDC, hBitmap);
		DeleteDC(hCompatibleDC);
		DeleteObject(hCompatibleDC);
		
		SetTextColor(hdc, RGB(255, 165, 0));
		SetBkMode(hdc,TRANSPARENT);
		//SetBkColor(hdc, RGB(0, 0, 0));
		wsprintf(str1, TEXT("India is my country and all Indians are my brothers and sisters."));
		wsprintf(str2, TEXT("I love my country and I am proud of its rich and varied heritage."));

		TextOut(hdc, TA_LEFT, TA_LEFT, TEXT(str1), strlen(str1));
		TextOut(hdc, TA_LEFT, 50, TEXT(str2), strlen(str2));		
		
		SetTextColor(hdc, RGB(255, 255, 255));
		wsprintf(str3, TEXT("I shall give respect to my parents, teachers and elders and treat"));
		wsprintf(str4, TEXT("everyone with courtesy. I shall always strive to be worthy of it."));
		TextOut(hdc, TA_LEFT, 150, str3, strlen(str3));
		TextOut(hdc, TA_LEFT, 200, str4, strlen(str4));
		
		SetTextColor(hdc, RGB(0, 128, 0));
		wsprintf(str5, TEXT("To my country and my people, I pledge my devotion."));
		wsprintf(str6, TEXT("In their well being and prosperity alone, lies my happiness."));	
		
		TextOut(hdc, TA_LEFT, 300, str5, strlen(str5));
		TextOut(hdc, TA_LEFT, 350, str6, strlen(str6));
		
		DeleteObject(hTmp);
		EndPaint(hwnd, &PS);
		break;	
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}