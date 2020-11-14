// MyProject01.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MyProject01.h"
//#include <gdiplus.h>

//#pragma comment(lib,"gdiplus")

#include <windowsx.h>


//using namespace Gdiplus;


// 전역변수 

unsigned char g_dol[Y_COUNT][X_COUNT];
unsigned char g_step;
unsigned int TimerA = 0;

// 구조체 선언 및 생성

typedef struct MousePost {
	int x = 0;
	int y = 0;
} MPos;

MPos mp;



// 전역함수 구현

void Timer()
{
	TimerA++;
	if (TimerA >= 10)
	{
		TimerA = 0;
		g_step = !(g_step);
	}
}

void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);

	//바둑 판 세로 가로 선 그리기 .

	for (int x = 0; x < X_COUNT; x++) {
		MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
		LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++) {
		MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
		LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
	}



	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (g_dol[y][x] > 0)
			{
				if (g_dol[y][x] == 1)
				{
					SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
				}
				else
				{
					SelectObject(h_dc, GetStockObject(WHITE_BRUSH));
				}
				Ellipse(h_dc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL
					, XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);

			}

		}
	}


	EndPaint(ah_wnd, &ps);
}


void OnLButtonDown(HWND ah_wnd, int a_x, int a_y)
{
	// 바둑 둘수있는 유효범위 
	if (a_x > (XPOS(0) - HALF_INTERVAL)
		&& a_y >(YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
		&& a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL) )
	{

		int x = (a_x - START_X + HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y + HALF_INTERVAL) / INTERVAL;
		if (g_dol[y][x] == 0)
		{
			g_dol[y][x] = g_step + 1;

			g_step = !(g_step);

			InvalidateRect(ah_wnd, NULL, TRUE);

			TimerA = 0; // 타이머 초기화 [바둑을 두면]
		}
	}
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
	}

	else if (uMsg == WM_CREATE)
	{
		SetTimer(hWnd, 1, 1000, NULL); //1번 타이머 
	}

	else if (uMsg == WM_LBUTTONDOWN) {
		// HDC h_dc = GetDC(hWnd);

		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		OnLButtonDown(hWnd, x, y);

		/*
		if ( MK_CONTROL & wParam ) Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);
		else Rectangle(h_dc, x - 15, y - 15, x + 15, y + 15);
		*/

		// ReleaseDC(hWnd, h_dc);
	}
	/*
	else if(uMsg == WM_KEYDOWN){
		HDC h_dc = GetDC(hWnd);


		if (VK_CONTROL & wParam) Ellipse(h_dc, mp.x - 15, mp.y - 15, mp.x + 15, mp.y + 15);
		else Rectangle(h_dc, mp.x - 15, mp.y - 15, mp.x + 15, mp.y + 15);
		ReleaseDC(hWnd, h_dc);
	}
	*/
	else if (uMsg == WM_MOUSEMOVE) {

		mp.y = GET_Y_LPARAM(lParam);
		mp.x = GET_X_LPARAM(lParam);


	}

	else if (uMsg == WM_PAINT) {

		OnPaint(hWnd);
		return 0;
	}

	else if (uMsg == WM_TIMER)
	{
		Timer();
	}

	



	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//ULONG_PTR gpToken;
	//GdiplusStartupInput gpsi;

	//if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok) return 0;



	WNDCLASS wc;


	// 브러쉬 생성 

	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));


	wchar_t my_class_name[] = L"tipssoft";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)h_bk_brush;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
	



	//윈도우 생성 []
	
	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com - 오목만들기 !!!",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//GdiplusShutdown(gpToken);
	DeleteObject(h_bk_brush);

	return msg.wParam;
}
