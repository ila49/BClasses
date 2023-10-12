// v.0.6-25.09.23

#include "SelFrame.h"
#include <tchar.h>

SelFrame::SelFrame()
{
	pSF = nullptr;
	result = FALSE;							// пока не инициализируем
	// задаём толщину и цвет по-умолчанию для рамки от ЛКМ
	LBLinePen = CreatePen(PS_SOLID,         // непрерывная линия
		                  0,                // толщина рамки - 1 пиксел
		                  RGB(255, 0, 0));  // цвет рамки от ЛКМ - красный
	// задаём толщину и цвет по-умолчанию для рамки от ПКМ
	RBLinePen = CreatePen(PS_DASH,          // пунктирная линия
		                  0,                // толщина рамки - 1 пиксел
		                  RGB(0, 255, 0));  // цвет рамки от ПКМ - зелёный
	tme = { 0,0,0,0 };						// пока не инициализируем
	LB_status = 0;
	RB_status = 0;
	rect = { 0,0,0,0 };						// пока не инициализируем
	ObjectMode = 1;							// отслеживать и отрисовывать обе КМ
	SkipLBRect = FALSE;
	LBDisabled = FALSE;
	SkipRBRect = FALSE;
	RBDisabled = FALSE;
	MouseLBX1 = MouseLBY1 = -1;	// положение не определено
	MouseLBX2 = MouseLBY2 = -1;
	MouseRBX1 = MouseRBY1 = -1;
	MouseRBX2 = MouseRBY2 = -1;
	hw = 0;									// пока не инициализируем
//	DoNotRedrawNC = FALSE;
}

void SelFrame::init(HWND HW, SelFrame* SFpointer)
{
	pSF = SFpointer;
	hw = HW;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = hw;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;
}


void SelFrame::wm_lbuttondown(int mouseXLB, int mouseYLB)
{
	if (LBDisabled || RB_status >= 1) return;
	MouseLBX1 = mouseXLB;
	MouseLBY1 = mouseYLB;
	MouseLBX2 = -1;			// положение не определено
	MouseLBY2 = -1;

	LB_status = 1;	// статус ЛКМ - нажата
//-\/ otladka
	rect = { 4,0,150,160 }; // область вывода координат курсора
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_lbuttonup(int mouseXLB, int mouseYLB)
{
	if (LBDisabled || RB_status >= 1) return;
	MouseLBX2 = mouseXLB;
	MouseLBY2 = mouseYLB;
	LB_status = 0;	// статус ЛКМ - отпущена
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_rbuttondown(int mouseXRB, int mouseYRB)
{
	if (RBDisabled || LB_status >= 1) return;
	MouseRBX1 = mouseXRB;
	MouseRBY1 = mouseYRB;
	MouseRBX2 = -1;			// положение не определено
	MouseRBY2 = -1;
	RB_status = 1;			// статус ПКМ - нажата
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_rbuttonup(int mouseXRB, int mouseYRB)
{
	if (RBDisabled || LB_status >= 1) return;
	MouseRBX2 = mouseXRB;
	MouseRBY2 = mouseYRB;
	RB_status = 0;	        // статус ПКМ - отпущена
//-\/ otladka
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};

void SelFrame::wm_paint(HDC hdc)
{
//*\/ otladka
	wchar_t wCh[100];
	RECT rect1 = { 4,0,150,20 };
	RECT rect2 = { 4,20,150,40 };
	RECT rect3 = { 4,40,150,60 };
	RECT rect4 = { 4,60,150,80 };
	RECT rect5 = { 4,80,150,100 };
	RECT rect6 = { 4,100,150,120 };
	RECT rect7 = { 4,120,150,140 };
	RECT rect8 = { 4,140,150,160 };
	swprintf(wCh, 100, L"х1 ЛКМ= %d\0", MouseLBX1);
	DrawText(hdc, wCh, -1, &rect1, DT_LEFT);
	swprintf(wCh, 100, L"y1 ЛКМ= %d\0", MouseLBY1);
	DrawText(hdc, wCh, -1, &rect2, DT_LEFT);
	swprintf(wCh, 100, L"х2 ЛКМ= %d\0", MouseLBX2);
	DrawText(hdc, wCh, -1, &rect3, DT_LEFT);
	swprintf(wCh, 100, L"y2 ЛКМ= %d\0", MouseLBY2);
	DrawText(hdc, wCh, -1, &rect4, DT_LEFT);
	swprintf(wCh, 100, L"x1 ПКМ= %d\0", MouseRBX1);
	DrawText(hdc, wCh, -1, &rect5, DT_LEFT);
	swprintf(wCh, 100, L"y1 ПКМ= %d\0", MouseRBY1);
	DrawText(hdc, wCh, -1, &rect6, DT_LEFT);
	swprintf(wCh, 100, L"x2 ПКМ= %d\0", MouseRBX2);
	DrawText(hdc, wCh, -1, &rect7, DT_LEFT);
	swprintf(wCh, 100, L"y2 ПКМ= %d\0", MouseRBY2);
	DrawText(hdc, wCh, -1, &rect8, DT_LEFT);
//	DoNotRedrawNC = TRUE;
//*/\ otladka
// рисуем рамку только когда ЛКМ нажата и нужно отрисовывать рамку
	if (!LBDisabled && LB_status == 2)
	{
		if (!SkipLBRect)
		{
			SelectObject(hdc, LBLinePen);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// рисовать только саму рамку
			result = Rectangle(hdc, MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2);
		}
		LB_status = 1;
//		DoNotRedrawNC = TRUE;
	}
	// рисуем рамку только когда ПКМ нажата и нужно отрисовывать рамку
	if (!RBDisabled && RB_status == 2)
	{
		if (!SkipRBRect)
		{
			SelectObject(hdc, RBLinePen);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// рисовать только саму рамку
			result = Rectangle(hdc, MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2);
		}
		RB_status = 1;
//		DoNotRedrawNC = TRUE;
	}
};

void SelFrame::wm_mousemove(int mouseX, int mouseY)
{
	if (!LBDisabled && LB_status == 1)
	{
		LB_status = 2;	// статус ЛКМ - нажата, нужно отрисовать рамку
		MouseLBX2 = mouseX;
		MouseLBY2 = mouseY;
		rect = {MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2}; // область вывода координат курсора
		InvalidateRect(0, &rect, TRUE);
		result = TrackMouseEvent(&tme);
	}
	if (!RBDisabled && RB_status == 1)
	{
		RB_status = 2;	// статус ПКМ - нажата, нужно отрисовать рамку
		MouseRBX2 = mouseX;
		MouseRBY2 = mouseY;
		rect = { MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2 }; // область вывода координат курсора
		InvalidateRect(0, &rect, TRUE);
		result = TrackMouseEvent(&tme);
	}
};

void SelFrame::wm_mouseleave()
{
	if (!LBDisabled && LB_status >= 1)
	{
		LB_status = 0;	// выключаем статус "ЛК нажата", даже если она остаётся нажатой
		rect = { MouseLBX1, MouseLBY1, MouseLBX2, MouseLBY2 };
		InvalidateRect(0, &rect, TRUE); // перерисовывает область из-под рамки но рамку не рисуем
//-\/ otladka перерисрвываем область с выводом координат курсора
		rect = { 4,0,150,160 };
		InvalidateRect(0, &rect, TRUE);
//-/\ otladka
	}
	if (!RBDisabled && RB_status >= 1)
	{
		RB_status = 0;	// выключаем статус "ПК нажата", даже если она остаётся нажатой
		rect = { MouseRBX1, MouseRBY1, MouseRBX2, MouseRBY2 };
		InvalidateRect(0, &rect, TRUE); // перерисовывает область из-под рамки но рамку не рисуем
//-\/ otladka перерисрвываем область с выводом координат курсора
		rect = { 4,0,150,160 };
		InvalidateRect(0, &rect, TRUE);
//-/\ otladka
	}
};

void SelFrame::SetMode(signed char ObjectMode)
{
	MouseLBX1 = MouseLBY1 = -1; // сбрасываем положение в неопределённое
	MouseLBX2 = MouseLBY2 = -1;
	MouseRBX1 = MouseRBY1 = -1;
	MouseRBX2 = MouseRBY2 = -1;
	switch (ObjectMode)
	{
		case 1:	    // Обе КМ: слежение и отрисовка
			LBDisabled = FALSE;
			RBDisabled = FALSE;
			SkipLBRect = FALSE;
			SkipRBRect = FALSE;
			LB_status = 0;
			RB_status = 0;
			break;
		case -1:	// Обе КМ: только слежение
			LBDisabled = FALSE;
			RBDisabled = FALSE;
			SkipLBRect = TRUE;
			SkipRBRect = TRUE;
			LB_status = 0;
			RB_status = 0;
			break;
		case 0:  	// Обе КМ: не работают
			LBDisabled = TRUE;
			RBDisabled = TRUE;
			SkipLBRect = TRUE;
			SkipRBRect = TRUE;
			LB_status = 0;
			RB_status = 0;
			break;
		case -2:	// ЛКМ: только слежение
			LBDisabled = FALSE;
			SkipLBRect = TRUE;
			LB_status = 0;
			break;
		case -3:	// ЛКМ: слежение и отрисовка
			LBDisabled = FALSE;
			SkipLBRect = FALSE;
			LB_status = 0;
			break;
		case -4:	// ЛКМ: не работает
			LBDisabled = TRUE;
			LB_status = 0;
			break;
		case 2:	    // ПКМ: только слежение
			RBDisabled = FALSE;
			SkipRBRect = TRUE;
			RB_status = 0;
			break;
		case 3:	    // ПКМ: слежение и отрисовка
			RBDisabled = FALSE;
			SkipRBRect = FALSE;
			RB_status = 0;
			break;
		case 4:	    // ПКМ: не работает
			RBDisabled = TRUE;
			RB_status = 0;
			break;
	}
//-\/ otladka перерисовываем область с выводом координат курсора
	rect = { 4,0,150,160 };
	InvalidateRect(0, &rect, TRUE);
//-/\ otladka
};
