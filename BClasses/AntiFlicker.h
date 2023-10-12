// v.0.1-28.04.23

#pragma once
#include <Windows.h>

class AntiFlicker
{
	BOOL res;
	HDC hdc;
	HBITMAP memBM;
	HGDIOBJ hGDI;

public:
	AntiFlicker();	// конструктор класса
	void wm_paint_0(HWND hWnd, HDC hdc, HBRUSH hbr);
	void wm_paint_1(HDC hdc);
	RECT CArect;
	HDC memDC;
};

