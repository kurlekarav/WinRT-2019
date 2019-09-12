#include<Windows.h>

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
	TCHAR str[255] = TEXT("Hello, Please press R/G/B/C/M/Y/K/W. I have something to tell you !!");
	static int iPaintFlag;
	HBRUSH HBrush;
	HFONT hFont;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch(LOWORD(wParam))
		{
			case 'R':
			case 'r':
				iPaintFlag = 1;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'G':
			case 'g':
				iPaintFlag = 2;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'B':
			case 'b':
				iPaintFlag = 3;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'C':
			case 'c':
				iPaintFlag = 4;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'M':
			case 'm':
				iPaintFlag = 5;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'Y':
			case 'y':
				iPaintFlag = 6;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'K':
			case 'k':
				iPaintFlag = 7;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			case 'W':
			case 'w':
				iPaintFlag = 8;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
		}
		break;

	case WM_PAINT:
		// get client area changing rectangle
		GetClientRect(hwnd, &RC);
		//call the specialist i.e create hdc
		hdc = BeginPaint(hwnd, &PS);
		SetTextColor(hdc, RGB(128,128,128));
		SetBkMode(hdc,TRANSPARENT);
		DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		SetTextColor(hdc, RGB(0,0,0));
		hFont=CreateFont(30,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,"SYSTEM_FIXED_FONT");
		switch(iPaintFlag)
		{
			case 1:
				wsprintf(str, TEXT("Red is the color of fire and blood, so "
									"it is associated with energy, war, danger, "
									"strength, power, determination as well as "
									"passion, desire, and love."));
				HBrush = CreateSolidBrush(RGB(255,0,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;

			case 2:
				wsprintf(str, TEXT("Green is the color of nature. It symbolizes growth, "
									"harmony, freshness, and fertility. Green has strong "
									"emotional correspondence with safety."));
				HBrush = CreateSolidBrush(RGB(0,255,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;

			case 3:
				wsprintf(str, TEXT("Blue is the color of the sky and sea. "
									"It is often associated with depth and "
									"stability. It symbolizes trust, loyalty, "
									"wisdom, confidence, intelligence, faith, "
									"truth, and heaven."));
				HBrush = CreateSolidBrush(RGB(0,0,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				SetTextColor(hdc, RGB(255, 255, 255));
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;
				
			case 4:
				wsprintf(str, TEXT("Cyan is a tint of blue that is found in the "
								   "spectrum of green and blue. Therefore, the "
								   "cyan color meaning is associated with both colors."));
				HBrush = CreateSolidBrush(RGB(0,255,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;				
				
			case 5:
				wsprintf(str, TEXT("Magenta has a connection to psychic world and psychic abilities.\r\n"
								   "It is believed that being in presence of magenta increases person's"
								   "connection to their spiritual side and enhances any psychic abilities that they may have"));
				HBrush = CreateSolidBrush(RGB(255,0,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				DrawText(hdc, str, -1, &RC, DT_CENTER | DT_VCENTER);
				break;

			case 6:

				wsprintf(str, TEXT("Yellow is the color of sunshine. It's associated with "
									"joy, happiness, intellect, and energy."));
				HBrush = CreateSolidBrush(RGB(255,255,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;

			case 7:
				wsprintf(str, TEXT("Black is associated with power, elegance, "
									"formality, death, evil, and mystery."));
				HBrush = CreateSolidBrush(RGB(0,0,0));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				SetTextColor(hdc, RGB(255, 255, 255));
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;

			case 8:
				wsprintf(str, TEXT("White is associated with light, goodness, "
									"innocence, purity. It is considered to be "
									"the color of perfection."));
				HBrush = CreateSolidBrush(RGB(255,255,255));
				SelectObject(hdc, HBrush);
				FillRect(hdc, &RC, HBrush);
				DrawText(hdc, str, -1, &RC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				break;
		}
		EndPaint(hwnd, &PS);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}