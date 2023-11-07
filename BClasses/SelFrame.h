// v.0.7-07.11.23

#pragma once
#include <wtypes.h>

class SelFrame
{
	BOOL result;
	HPEN LBLinePen, RBLinePen;
	TRACKMOUSEEVENT tme;
	RECT rect;
	signed char ObjectMode;
	BOOL SkipLBRect, LBDisabled, SkipRBRect, RBDisabled;

public:
	SelFrame* pSF;
	unsigned char LB_status, LB_status_pr, RB_status, RB_status_pr, LB_mouseleave, RB_mouseleave;
	int MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2, MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2;
	HWND hw;
//	BOOL DoNotRedrawNC;
	SelFrame();						// конструктор класса
	void init(HWND HW, SelFrame*);
	void wm_lbuttondown(int, int);
	void wm_lbuttonup(int, int);
	void wm_rbuttondown(int, int);
	void wm_rbuttonup(int, int);
	void wm_paint(HDC hdc);
	void wm_mousemove(int mouseX, int mouseY);
	void wm_mouseleave();
	void SetMode(signed char ObjectMode);
};

