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
    res = BitBlt(hdc,               // �������� ������� � hdc
                 0,                 // �-���������� ������ �������� ���� BitMap-��������
                 0,                 // y-���������� ������ �������� ���� BitMap-��������
                 CArect.right,      // ������ ������� ��������� � ��������
                 CArect.bottom,     // ������ ������� ��������� � ��������
                 memDC,             // �������� ������� �� memDC 
                 0,                 // �-���������� ������ �������� ���� BitMap-���������
                 0,                 // y-���������� ������ �������� ���� BitMap-���������
                 SRCCOPY            // Copies the source rectangle directly to the destination rectangle
                 );
    DeleteObject(memBM);
    DeleteObject(memDC);
}
