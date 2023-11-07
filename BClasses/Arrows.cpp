// v.0.7-07.11.23

#include "Arrows.h"
#include "SelFrame.h"

// x1 - экранная х-координата начала стрелки
// y1 - экранная у-координата начала стрелки
// x2 - экранная х-координата конца стрелки
// y2 - экранная у-координата конца стрелки
// l - длина усов стрелки в пикселях (от точек 3/4 до точки 2)
// w - ширина усов стрелки в пикселях
// b - длина основания усов стрелки в пикселах (от точек 7/8 до точки 2)
// L_fade - длина стрелки в пикселах, меньше которой пропроцилнально уменьшать длину и ширину усов

Arrows::Arrows()	// конструктор класса
{
	mode.type = { 0 };
	mode.button = { 0 };
	mode.style = { 1 };
	mode.type2 = { 0 };
	mode.type2_LB = { 0 };
	mode.type2_RB = { 0 };
	alf_r = { 0.0 };
	fix_r = { 0.0 };
	dx = { 0.0 };
	dy = { 0.0 };
	L = { 0.0 };
	Sin = { 0.0 };
	Cos = { 0.0 };
	x34 = { 0.0 };
	x78 = { 0.0 };
	y = { 0.0 };
	y5678 = { 0.0 };
	x34Cos = { 0.0 };
	x78Cos = { 0.0 };
	ySin = { 0.0 };
	y5678Sin = { 0.0 };
	x34Sin = { 0.0 };
	x78Sin = { 0.0 };
	yCos = { 0.0 };
	y5678Cos = { 0.0 };
	p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = p[6] = p[7] = {-1,-1};
	res = 0;
// буфер состоит из 16 чисел типа int, которые содержат экранные координаты x и y 8 (максимально, в случае объёмной стрелки) 
// узловых точек стрелки. Один буфер - это 8 элементов типа POINT. Если в первом элементе в буфера (координаты точки 1) -1,
// это означает, что в буфере нет достоверных координат любой стрелки. Если в четвёртом (координаты точки 4), это означает,
// что в данном буфере нет достоверных координат объёмной стрелки.
	ar_p.assign(32, p[0]);		// инициализируем 4 буфера (0, 1, 2 и 3) - пул буферов
	K = 0;
	Point = { 0,0 };
	buf_N = { 0 };
	buf_i = { 0 };


//-\/ otladka
	// буфер 2
	ar_p[16].x = 100;	// точка 1
	ar_p[16].y = 100;
	ar_p[17].x = 800;	// точка 2
	ar_p[17].y = 800;
	ar_p[18].x = 780;	// точка 3
	ar_p[18].y = 650;
	ar_p[23].x = 650;	// точка 8
	ar_p[23].y = 780;
	// буфер 3
	ar_p[24].x = 500;	// точка 1
	ar_p[24].y = 100;
	ar_p[25].x = 500;	// точка 2
	ar_p[25].y = 600;
	ar_p[26].x = 550;	// точка 3
	ar_p[26].y = 500;
	ar_p[27].x = 520;	// точка 4
	ar_p[27].y = 500;
	ar_p[28].x = 520;	// точка 5
	ar_p[28].y = 100;
	ar_p[29].x = 480;	// точка 6
	ar_p[29].y = 100;
	ar_p[30].x = 480;	// точка 7
	ar_p[30].y = 500;
	ar_p[31].x = 450;	// точка 8
	ar_p[31].y = 500;
//-/\ otladka

}

int Arrows::calc_1(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w, unsigned short L_fade)
{
	// Функция вычисляет экранные координаты точек 3 и 8 по заданным координатам точек 1 и 2
	// используется для рисования плоской стрелки
	// L_fade - длина стрелки в пикселах, меньше которой пропроцилнально уменьшать длину и ширину усов (если =0, то не
	// уменьшать)
	// коды возврата:
	// 0 - ошибок нет
	// 1 - ошибка, неправильно задана длина усов стрелки, l
	// 2 - ошибка, неправильно задан угол заострения усов стрелки (0 < должен быть < 90)
	// 3 - стрелка вырождена в точку, ничего не рисуем
	if (l == 0.0) return 1;							// код 1 - неправильно задана длина усов стрелки, l
	alf_r = atan(0.5 * w / l);
	if (alf_r <= 0.0 || alf_r >= M_PI_2) return 2;	// код 2 - неправильно задан угол заострения усов стрелки (0 < должен быть < 90)
	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// стрелка перпендикулярна плоскости рисования
		{
			// рисуем точку? и сообщаем об этом кодом 3
			return 3;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// стрелка строго вниз
		}
		else
		{
			fix_r = -M_PI_2;	// стрелка строго вверх
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// пропорционально уменьшаем размеры узов стрелки начиная с некоторой минимальной длины стрелки
	{
		if (L < L_fade)
		{
			K = L / L_fade;
			l = round(l * K);
			w = round(w * K);
		}
	}
	Sin = sin(fix_r);
	Cos = cos(fix_r);
	x34 = (double)(L - l);
	y = -0.5 * w;
	x34Cos = x34 * Cos;
	ySin = y * Sin;
	x34Sin = x34 * Sin;
	yCos = y * Cos;
	ar_p[buf_N].x = x1;											// координата х точки 1
	ar_p[buf_N].y = y1;											// координата у точки 1
	ar_p[buf_N + 1].x = x2;										// координата х точки 2
	ar_p[buf_N + 1].y = y2;										// координата у точки 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));		// координата х точки 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	    // координата у точки 3
	ar_p[buf_N + 3].x = -1;		                                // координата х точки 4 недействительна
	ar_p[buf_N + 3].y = -1;		                                // координата у точки 4 недействительна
	ar_p[buf_N + 4].x = -1;				                        // координата х точки 5 недействительна
	ar_p[buf_N + 4].y = -1;				                        // координата у точки 5 недействительна
	ar_p[buf_N + 5].x = -1;				                        // координата х точки 6 недействительна
	ar_p[buf_N + 5].y = -1;				                        // координата у точки 6 недействительна
	ar_p[buf_N + 6].x = -1;	                                    // координата х точки 7 недействительна
	ar_p[buf_N + 6].y = -1;	                                    // координата у точки 7 недействительна
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	    // координата х точки 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	    // координата у точки 8

	return 0;
}

void Arrows::draw_1(HDC hdc, POINT* pp)
{
// для совместимости принимаем адрес массива структур типа POINT (pp) из 8 элементов (в классе Arrows этот адрес не
// используется, вне класса нужно использовать 1-4 элементы)
	MoveToEx(hdc, p[0].x, p[0].y, &Point);
	LineTo(hdc, p[1].x, p[1].y);
	LineTo(hdc, p[2].x, p[2].y);
	MoveToEx(hdc, p[1].x, p[1].y, &Point);
	LineTo(hdc, p[3].x, p[3].y);
}

int Arrows::test_2(unsigned short l, unsigned short w, unsigned short s, unsigned short b)
{
	if (l == 0) return 1; // неправильно задана длина усов стрелки
	if (b == 0) return 2; // неправильно задана длина основания усов стрелки
	if (s < 2) return 3;  // неправильно задана толщина стрелки
	alf_r = atan(0.5 * w / l);
	if (alf_r <= 0.0 || alf_r >= M_PI_2) return 4; // неправильно задан угол заострения усов стрелки(0 < должен быть < 90)
	if (w / l < s / b) return 5; // неправильноe соотношение толщины и конфигурации усов стрелки
	return 0;
}

int Arrows::calc_2(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w,
				   unsigned short s, unsigned short b, unsigned short L_fade)
{	// buf_N - начальный индекс в буфере координат
	// L_fade - длина стрелки в пикселах, меньше которой пропроцилнально уменьшать длину и ширину усов (если =0, то не
	//  уменьшать)
	// s - ширина стрелки в пикселах
	// l - длина усов стрелки в пикселах
	// b - основание усов стрелки в пикселах
	// коды возврата:
	// 0 - ошибок нет
	// 1 - стрелка вырождена в точку
	
	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// стрелка перпендикулярна плоскости рисования
		{
			// рисуем точку? и сообщаем об этом кодом 1
			return 1;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// стрелка строго вниз
		}
		else
		{
			fix_r = -M_PI_2;	// стрелка строго вверх
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// пропорционально уменьшаем размеры узов стрелки начиная с некоторой минимальной длины стрелки
	{
		if (L < L_fade)
		{
			K = L / L_fade;
			l = round(l * K);
			w = round(w * K);
			b = round(b * K);
			s = round(s * K);
		}
	}
	Sin = sin(fix_r);
	Cos = cos(fix_r);
	x34 = (double)(L - l);
	x78 = (double)(L - b);
	y = -0.5 * w;
	y5678 = -0.5 * s;
	x34Cos = x34 * Cos;
	x78Cos = x78 * Cos;
	ySin = y * Sin;
	y5678Sin = y5678 * Sin;
	x34Sin = x34 * Sin;
	x78Sin = x78 * Sin;
	yCos = y * Cos;
	y5678Cos = y5678 * Cos;
	ar_p[buf_N].x = x1;											// координата х точки 1
	ar_p[buf_N].y = y1;											// координата у точки 1
	ar_p[buf_N + 1].x = x2;											// координата х точки 2
	ar_p[buf_N + 1].y = y2;											// координата у точки 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));			// координата х точки 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	        // координата у точки 3
	ar_p[buf_N + 3].x = (int)(x1 + round(x78Cos - y5678Sin));		// координата х точки 4
	ar_p[buf_N + 3].y = (int)(y1 + round(x78Sin + y5678Cos));		// координата у точки 4
	ar_p[buf_N + 4].x = (int)(x1 + round(-y5678Sin));				// координата х точки 5
	ar_p[buf_N + 4].y = (int)(y1 + round(y5678Cos));				// координата у точки 5
	ar_p[buf_N + 5].x = (int)(x1 + round(y5678Sin));				// координата х точки 6
	ar_p[buf_N + 5].y = (int)(y1 + round(-y5678Cos));				// координата у точки 6
	ar_p[buf_N + 6].x = (int)(x1 + round(x78Cos + y5678Sin));	    // координата х точки 7
	ar_p[buf_N + 6].y = (int)(y1 + round(x78Sin - y5678Cos));	    // координата у точки 7
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	        // координата х точки 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	        // координата у точки 8

	return 0;
}

void Arrows::draw_2(HDC hdc, unsigned int buf_N)
{
// рисуем полигон от точки 2 до точки 8
	Polygon(hdc, &ar_p[buf_N + 1], 7);	// пропускаем точку 1
}

int Arrows::wm_paint(HDC hdc, SelFrame* pSF, int* pbuf, unsigned int buf, unsigned short l, unsigned short w,
	                 unsigned short s, unsigned short b, unsigned short L_fade)
{
// mode.type=0 - сразу выходим из функции, ничего не рисуем
// mode.type=1 - рисуем стрелки из пула буферов: pbuf[0] - количество буферов, которые надо отобразить, pbuf[1], pbuf[2]... - номера
//  буферов, если номер < 0, то рисуем объёмную стрелку, если >= 0 - то плоскую.
// mode.type=2 - рассчитываем и рисуем стрелку, заполняем buf - номер буфера, в который сохраняем
//  расчитанные данные (при других mode.type эта переменная не имеет значения); (стрелка пропадает сразу же после отпускания ЛКМ)
	if (mode.type == 0) return 0;
//	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // стрелку невозможно нарисовать, т.к. одна из координат не определена
	else if (mode.type == 1) // только рисуем стрелки из пула буферов
	{
		for (int i = 1; i <= pbuf[0]; ++i)
		{
			if (pbuf[i] < 0) draw2(hdc, -pbuf[i]);	    // рисуем объёмную стрелку
			else draw1(hdc, pbuf[i]);				    // рисуем плоскую стрелку
		}
		return 0;
	}
	else if (mode.type == 2)
	{
		if (mode.button == 1 || mode.button == 3)	    // работаем с ЛКМ или с обеими КМ
		{

			if (mode.type2_LB == 2 && pSF->LB_mouseleave == 1) pSF->LB_mouseleave = 0;	   // режим В
			else if (mode.type2_LB >= 1 && pSF->LB_status == 0 && pSF->LB_status_pr >= 1)  // режим Б
			{
				switch (mode.style)
				{
				case 1:
					draw1(hdc, buf);	 // рисуем плоскую стрелку
					break;
				case 2:
					draw2(hdc, buf);	 // рисуем объёмную стрелку
					break;
				}
			}
			else if (pSF->LB_status == 1) // работаем с ЛКМ
			{
				int x1 = pSF->MouseLBX1;
				int y1 = pSF->MouseLBY1;
				int x2 = pSF->MouseLBX2;
				int y2 = pSF->MouseLBY2;
				if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // стрелку невозможно нарисовать, т.к. одна из координат не определена
				switch (mode.style)
				{
				case 1:		             // рисуем плоскую стрелку
					res = calc_1(buf * 8, x1, y1, x2, y2, l, w, L_fade);
					if (res == 0)
					{
						draw1(hdc, buf);
						return res;
					}
					break;
				case 2:		             // рисуем объёмную стрелку
					res = calc2(buf * 8, x1, y1, x2, y2, l, w, s, b, L_fade);
					if (res == 0)
					{
						draw2(hdc, buf);
						return res;
					}
					break;
				}

			}
		}
		if (mode.button == 2 || mode.button == 3)       // работаем с ПКМ или с обеими КМ
		{
			if (mode.type2_RB == 2 && pSF->RB_mouseleave == 1) pSF->RB_mouseleave = 0;	    // режим В
			else if (mode.type2_RB >= 1 && pSF->RB_status == 0 && pSF->RB_status_pr >= 1)   // режим Б
			{
				switch (mode.style)
				{
				case 1:
					draw1(hdc, buf);	// рисуем плоскую стрелку
					break;
				case 2:
					draw2(hdc, buf);	// рисуем объёмную стрелку
					break;
				}
			}
			else if (pSF->RB_status == 1) // работаем с ПКМ
			{
				int x1 = pSF->MouseRBX1;
				int y1 = pSF->MouseRBY1;
				int x2 = pSF->MouseRBX2;
				int y2 = pSF->MouseRBY2;
				if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // стрелку невозможно нарисовать, т.к. одна из координат не определена
				res = calc2(buf * 8, x1, y1, x2, y2, l, w, s, b, L_fade);
				switch (mode.style)
				{
				case 1:		// рисуем плоскую стрелку
					res = calc_1(buf * 8, x1, y1, x2, y2, l, w, L_fade);
					if (res == 0)
					{
						draw1(hdc, buf);
						return res;
					}
					break;
				case 2:		// рисуем объёмную стрелку
					res = calc2(buf * 8, x1, y1, x2, y2, l, w, s, b, L_fade);
					if (res == 0)
					{
						draw2(hdc, buf);
						return res;
					}
					break;
				}
			}
		}
	}
	return 0;
}

void Arrows::draw1(HDC hdc, unsigned int buf)
// Отрисовка плоской стрелки
// buf - номер буфера, в котором находятся экранные координаты стрелки (точки 1, 2, 3 и 8)
{
	buf_i = buf * 8;								        // нач. индекс буфера
	MoveToEx(hdc, ar_p[buf_i].x, ar_p[buf_i].y, &Point);	// точка 1
	buf_i += 1;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // точка 2
	buf_i += 1;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // точка 3
	buf_i -= 1;
	MoveToEx(hdc, ar_p[buf_i].x, ar_p[buf_i].y, &Point);    // точка 2
	buf_i += 6;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // точка 8
}

void Arrows::draw2(HDC hdc, unsigned int buf)
// Отрисовка объёмной стрелки
// buf - номер буфера, в котором находятся экранные координаты стрелки (точки 1 - 8)
{
	// рисуем полигон от точки 2 до точки 8
	Polygon(hdc, &ar_p[buf * 8 + 1], 7);	// пропускаем точку 1
}

int Arrows::calc2(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w,
				  unsigned short s, unsigned short b, unsigned short L_fade)
{	// buf_N - начальный индекс в буфере координат
	// L_fade - дина стрелки в пикселах, меньше которой пропроцилнально уменьшать длину и ширину усов (если =0, то не
	// уменьшать)
	// w - ширина усов стрелки в пикселах
	// s - ширина стрелки в пикселах
	// l - длина усов стрелки в пикселах
	// b - основание усов стрелки в пикселах
	// коды возврата:
	// 0 - ошибок нет
	// 1 - стрелка вырождена в точку

	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// стрелка перпендикулярна плоскости рисования
		{
			// рисуем точку? и сообщаем об этом кодом 1
			return 1;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// стрелка строго вниз
		}
		else
		{
			fix_r = -M_PI_2;	// стрелка строго вверх
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// пропорционально уменьшаем размеры узов стрелки начиная с некоторой минимальной длины стрелки
	{
		if (L < L_fade)
		{
			K = L / L_fade;
			l = round(l * K);
			w = round(w * K);
			b = round(b * K);
			s = round(s * K);
		}
	}
	Sin = sin(fix_r);
	Cos = cos(fix_r);
	x34 = (double)(L - l);
	x78 = (double)(L - b);
	y = -0.5 * w;
	y5678 = -0.5 * s;
	x34Cos = x34 * Cos;
	x78Cos = x78 * Cos;
	ySin = y * Sin;
	y5678Sin = y5678 * Sin;
	x34Sin = x34 * Sin;
	x78Sin = x78 * Sin;
	yCos = y * Cos;
	y5678Cos = y5678 * Cos;
	ar_p[buf_N].x = x1;												// координата х точки 1
	ar_p[buf_N].y = y1;												// координата у точки 1
	ar_p[buf_N + 1].x = x2;											// координата х точки 2
	ar_p[buf_N + 1].y = y2;											// координата у точки 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));			// координата х точки 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	        // координата у точки 3
	ar_p[buf_N + 3].x = (int)(x1 + round(x78Cos - y5678Sin));		// координата х точки 4
	ar_p[buf_N + 3].y = (int)(y1 + round(x78Sin + y5678Cos));		// координата у точки 4
	ar_p[buf_N + 4].x = (int)(x1 + round(-y5678Sin));				// координата х точки 5
	ar_p[buf_N + 4].y = (int)(y1 + round(y5678Cos));				// координата у точки 5
	ar_p[buf_N + 5].x = (int)(x1 + round(y5678Sin));				// координата х точки 6
	ar_p[buf_N + 5].y = (int)(y1 + round(-y5678Cos));				// координата у точки 6
	ar_p[buf_N + 6].x = (int)(x1 + round(x78Cos + y5678Sin));	    // координата х точки 7
	ar_p[buf_N + 6].y = (int)(y1 + round(x78Sin - y5678Cos));	    // координата у точки 7
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	        // координата х точки 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	        // координата у точки 8

	return 0;
}
