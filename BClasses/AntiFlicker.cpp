// v.0.1-28.04.23

#include "AntiFlicker.h"

AntiFlicker::AntiFlicker()
{
	res = FALSE;
    hdc = NULL;
    memBM = {};
    hGDI = {};
	CArect = { 0,0,0,0 };
    memDC = {};
}

void AntiFlicker::wm_paint_0(HWND hWnd, HDC hdc, HBRUSH hbr)
{
	res = GetClientRect(hWnd, &CArect);
	memDC = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, CArect.right, CArect.bottom);
	hGDI = SelectObject(memDC, memBM);
	FillRect(memDC, &CArect, hbr);
}

void AntiFlicker::wm_paint_1(HDC hdc)
{
    res = BitBlt(hdc,               // копируем пиксели в hdc
                 0,                 // х-координата левого верхнего угла BitMap-приёмника
                 0,                 // y-координата левого верхнего угла BitMap-приёмника
                 CArect.right,      // ширина области источника и приёмника
                 CArect.bottom,     // высота области источника и приёмника
                 memDC,             // копируем пиксели из memDC 
                 0,                 // х-координата левого верхнего угла BitMap-источника
                 0,                 // y-координата левого верхнего угла BitMap-источника
                 SRCCOPY            // Copies the source rectangle directly to the destination rectangle
                 );
    DeleteObject(memBM);
    DeleteObject(memDC);
}
