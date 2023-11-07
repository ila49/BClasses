// v.0.7-07.11.23

#include "Arrows.h"
#include "SelFrame.h"

// x1 - �������� �-���������� ������ �������
// y1 - �������� �-���������� ������ �������
// x2 - �������� �-���������� ����� �������
// y2 - �������� �-���������� ����� �������
// l - ����� ���� ������� � �������� (�� ����� 3/4 �� ����� 2)
// w - ������ ���� ������� � ��������
// b - ����� ��������� ���� ������� � �������� (�� ����� 7/8 �� ����� 2)
// L_fade - ����� ������� � ��������, ������ ������� ��������������� ��������� ����� � ������ ����

Arrows::Arrows()	// ����������� ������
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
// ����� ������� �� 16 ����� ���� int, ������� �������� �������� ���������� x � y 8 (�����������, � ������ �������� �������) 
// ������� ����� �������. ���� ����� - ��� 8 ��������� ���� POINT. ���� � ������ �������� � ������ (���������� ����� 1) -1,
// ��� ��������, ��� � ������ ��� ����������� ��������� ����� �������. ���� � �������� (���������� ����� 4), ��� ��������,
// ��� � ������ ������ ��� ����������� ��������� �������� �������.
	ar_p.assign(32, p[0]);		// �������������� 4 ������ (0, 1, 2 � 3) - ��� �������
	K = 0;
	Point = { 0,0 };
	buf_N = { 0 };
	buf_i = { 0 };


//-\/ otladka
	// ����� 2
	ar_p[16].x = 100;	// ����� 1
	ar_p[16].y = 100;
	ar_p[17].x = 800;	// ����� 2
	ar_p[17].y = 800;
	ar_p[18].x = 780;	// ����� 3
	ar_p[18].y = 650;
	ar_p[23].x = 650;	// ����� 8
	ar_p[23].y = 780;
	// ����� 3
	ar_p[24].x = 500;	// ����� 1
	ar_p[24].y = 100;
	ar_p[25].x = 500;	// ����� 2
	ar_p[25].y = 600;
	ar_p[26].x = 550;	// ����� 3
	ar_p[26].y = 500;
	ar_p[27].x = 520;	// ����� 4
	ar_p[27].y = 500;
	ar_p[28].x = 520;	// ����� 5
	ar_p[28].y = 100;
	ar_p[29].x = 480;	// ����� 6
	ar_p[29].y = 100;
	ar_p[30].x = 480;	// ����� 7
	ar_p[30].y = 500;
	ar_p[31].x = 450;	// ����� 8
	ar_p[31].y = 500;
//-/\ otladka

}

int Arrows::calc_1(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w, unsigned short L_fade)
{
	// ������� ��������� �������� ���������� ����� 3 � 8 �� �������� ����������� ����� 1 � 2
	// ������������ ��� ��������� ������� �������
	// L_fade - ����� ������� � ��������, ������ ������� ��������������� ��������� ����� � ������ ���� (���� =0, �� ��
	// ���������)
	// ���� ��������:
	// 0 - ������ ���
	// 1 - ������, ����������� ������ ����� ���� �������, l
	// 2 - ������, ����������� ����� ���� ���������� ���� ������� (0 < ������ ���� < 90)
	// 3 - ������� ��������� � �����, ������ �� ������
	if (l == 0.0) return 1;							// ��� 1 - ����������� ������ ����� ���� �������, l
	alf_r = atan(0.5 * w / l);
	if (alf_r <= 0.0 || alf_r >= M_PI_2) return 2;	// ��� 2 - ����������� ����� ���� ���������� ���� ������� (0 < ������ ���� < 90)
	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// ������� ��������������� ��������� ���������
		{
			// ������ �����? � �������� �� ���� ����� 3
			return 3;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// ������� ������ ����
		}
		else
		{
			fix_r = -M_PI_2;	// ������� ������ �����
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// ��������������� ��������� ������� ���� ������� ������� � ��������� ����������� ����� �������
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
	ar_p[buf_N].x = x1;											// ���������� � ����� 1
	ar_p[buf_N].y = y1;											// ���������� � ����� 1
	ar_p[buf_N + 1].x = x2;										// ���������� � ����� 2
	ar_p[buf_N + 1].y = y2;										// ���������� � ����� 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));		// ���������� � ����� 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	    // ���������� � ����� 3
	ar_p[buf_N + 3].x = -1;		                                // ���������� � ����� 4 ���������������
	ar_p[buf_N + 3].y = -1;		                                // ���������� � ����� 4 ���������������
	ar_p[buf_N + 4].x = -1;				                        // ���������� � ����� 5 ���������������
	ar_p[buf_N + 4].y = -1;				                        // ���������� � ����� 5 ���������������
	ar_p[buf_N + 5].x = -1;				                        // ���������� � ����� 6 ���������������
	ar_p[buf_N + 5].y = -1;				                        // ���������� � ����� 6 ���������������
	ar_p[buf_N + 6].x = -1;	                                    // ���������� � ����� 7 ���������������
	ar_p[buf_N + 6].y = -1;	                                    // ���������� � ����� 7 ���������������
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	    // ���������� � ����� 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	    // ���������� � ����� 8

	return 0;
}

void Arrows::draw_1(HDC hdc, POINT* pp)
{
// ��� ������������� ��������� ����� ������� �������� ���� POINT (pp) �� 8 ��������� (� ������ Arrows ���� ����� ��
// ������������, ��� ������ ����� ������������ 1-4 ��������)
	MoveToEx(hdc, p[0].x, p[0].y, &Point);
	LineTo(hdc, p[1].x, p[1].y);
	LineTo(hdc, p[2].x, p[2].y);
	MoveToEx(hdc, p[1].x, p[1].y, &Point);
	LineTo(hdc, p[3].x, p[3].y);
}

int Arrows::test_2(unsigned short l, unsigned short w, unsigned short s, unsigned short b)
{
	if (l == 0) return 1; // ����������� ������ ����� ���� �������
	if (b == 0) return 2; // ����������� ������ ����� ��������� ���� �������
	if (s < 2) return 3;  // ����������� ������ ������� �������
	alf_r = atan(0.5 * w / l);
	if (alf_r <= 0.0 || alf_r >= M_PI_2) return 4; // ����������� ����� ���� ���������� ���� �������(0 < ������ ���� < 90)
	if (w / l < s / b) return 5; // �����������e ����������� ������� � ������������ ���� �������
	return 0;
}

int Arrows::calc_2(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w,
				   unsigned short s, unsigned short b, unsigned short L_fade)
{	// buf_N - ��������� ������ � ������ ���������
	// L_fade - ����� ������� � ��������, ������ ������� ��������������� ��������� ����� � ������ ���� (���� =0, �� ��
	//  ���������)
	// s - ������ ������� � ��������
	// l - ����� ���� ������� � ��������
	// b - ��������� ���� ������� � ��������
	// ���� ��������:
	// 0 - ������ ���
	// 1 - ������� ��������� � �����
	
	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// ������� ��������������� ��������� ���������
		{
			// ������ �����? � �������� �� ���� ����� 1
			return 1;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// ������� ������ ����
		}
		else
		{
			fix_r = -M_PI_2;	// ������� ������ �����
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// ��������������� ��������� ������� ���� ������� ������� � ��������� ����������� ����� �������
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
	ar_p[buf_N].x = x1;											// ���������� � ����� 1
	ar_p[buf_N].y = y1;											// ���������� � ����� 1
	ar_p[buf_N + 1].x = x2;											// ���������� � ����� 2
	ar_p[buf_N + 1].y = y2;											// ���������� � ����� 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));			// ���������� � ����� 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	        // ���������� � ����� 3
	ar_p[buf_N + 3].x = (int)(x1 + round(x78Cos - y5678Sin));		// ���������� � ����� 4
	ar_p[buf_N + 3].y = (int)(y1 + round(x78Sin + y5678Cos));		// ���������� � ����� 4
	ar_p[buf_N + 4].x = (int)(x1 + round(-y5678Sin));				// ���������� � ����� 5
	ar_p[buf_N + 4].y = (int)(y1 + round(y5678Cos));				// ���������� � ����� 5
	ar_p[buf_N + 5].x = (int)(x1 + round(y5678Sin));				// ���������� � ����� 6
	ar_p[buf_N + 5].y = (int)(y1 + round(-y5678Cos));				// ���������� � ����� 6
	ar_p[buf_N + 6].x = (int)(x1 + round(x78Cos + y5678Sin));	    // ���������� � ����� 7
	ar_p[buf_N + 6].y = (int)(y1 + round(x78Sin - y5678Cos));	    // ���������� � ����� 7
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	        // ���������� � ����� 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	        // ���������� � ����� 8

	return 0;
}

void Arrows::draw_2(HDC hdc, unsigned int buf_N)
{
// ������ ������� �� ����� 2 �� ����� 8
	Polygon(hdc, &ar_p[buf_N + 1], 7);	// ���������� ����� 1
}

int Arrows::wm_paint(HDC hdc, SelFrame* pSF, int* pbuf, unsigned int buf, unsigned short l, unsigned short w,
	                 unsigned short s, unsigned short b, unsigned short L_fade)
{
// mode.type=0 - ����� ������� �� �������, ������ �� ������
// mode.type=1 - ������ ������� �� ���� �������: pbuf[0] - ���������� �������, ������� ���� ����������, pbuf[1], pbuf[2]... - ������
//  �������, ���� ����� < 0, �� ������ �������� �������, ���� >= 0 - �� �������.
// mode.type=2 - ������������ � ������ �������, ��������� buf - ����� ������, � ������� ���������
//  ����������� ������ (��� ������ mode.type ��� ���������� �� ����� ��������); (������� ��������� ����� �� ����� ���������� ���)
	if (mode.type == 0) return 0;
//	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // ������� ���������� ����������, �.�. ���� �� ��������� �� ����������
	else if (mode.type == 1) // ������ ������ ������� �� ���� �������
	{
		for (int i = 1; i <= pbuf[0]; ++i)
		{
			if (pbuf[i] < 0) draw2(hdc, -pbuf[i]);	    // ������ �������� �������
			else draw1(hdc, pbuf[i]);				    // ������ ������� �������
		}
		return 0;
	}
	else if (mode.type == 2)
	{
		if (mode.button == 1 || mode.button == 3)	    // �������� � ��� ��� � ������ ��
		{

			if (mode.type2_LB == 2 && pSF->LB_mouseleave == 1) pSF->LB_mouseleave = 0;	   // ����� �
			else if (mode.type2_LB >= 1 && pSF->LB_status == 0 && pSF->LB_status_pr >= 1)  // ����� �
			{
				switch (mode.style)
				{
				case 1:
					draw1(hdc, buf);	 // ������ ������� �������
					break;
				case 2:
					draw2(hdc, buf);	 // ������ �������� �������
					break;
				}
			}
			else if (pSF->LB_status == 1) // �������� � ���
			{
				int x1 = pSF->MouseLBX1;
				int y1 = pSF->MouseLBY1;
				int x2 = pSF->MouseLBX2;
				int y2 = pSF->MouseLBY2;
				if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // ������� ���������� ����������, �.�. ���� �� ��������� �� ����������
				switch (mode.style)
				{
				case 1:		             // ������ ������� �������
					res = calc_1(buf * 8, x1, y1, x2, y2, l, w, L_fade);
					if (res == 0)
					{
						draw1(hdc, buf);
						return res;
					}
					break;
				case 2:		             // ������ �������� �������
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
		if (mode.button == 2 || mode.button == 3)       // �������� � ��� ��� � ������ ��
		{
			if (mode.type2_RB == 2 && pSF->RB_mouseleave == 1) pSF->RB_mouseleave = 0;	    // ����� �
			else if (mode.type2_RB >= 1 && pSF->RB_status == 0 && pSF->RB_status_pr >= 1)   // ����� �
			{
				switch (mode.style)
				{
				case 1:
					draw1(hdc, buf);	// ������ ������� �������
					break;
				case 2:
					draw2(hdc, buf);	// ������ �������� �������
					break;
				}
			}
			else if (pSF->RB_status == 1) // �������� � ���
			{
				int x1 = pSF->MouseRBX1;
				int y1 = pSF->MouseRBY1;
				int x2 = pSF->MouseRBX2;
				int y2 = pSF->MouseRBY2;
				if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1; // ������� ���������� ����������, �.�. ���� �� ��������� �� ����������
				res = calc2(buf * 8, x1, y1, x2, y2, l, w, s, b, L_fade);
				switch (mode.style)
				{
				case 1:		// ������ ������� �������
					res = calc_1(buf * 8, x1, y1, x2, y2, l, w, L_fade);
					if (res == 0)
					{
						draw1(hdc, buf);
						return res;
					}
					break;
				case 2:		// ������ �������� �������
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
// ��������� ������� �������
// buf - ����� ������, � ������� ��������� �������� ���������� ������� (����� 1, 2, 3 � 8)
{
	buf_i = buf * 8;								        // ���. ������ ������
	MoveToEx(hdc, ar_p[buf_i].x, ar_p[buf_i].y, &Point);	// ����� 1
	buf_i += 1;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // ����� 2
	buf_i += 1;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // ����� 3
	buf_i -= 1;
	MoveToEx(hdc, ar_p[buf_i].x, ar_p[buf_i].y, &Point);    // ����� 2
	buf_i += 6;
	LineTo(hdc, ar_p[buf_i].x, ar_p[buf_i].y);			    // ����� 8
}

void Arrows::draw2(HDC hdc, unsigned int buf)
// ��������� �������� �������
// buf - ����� ������, � ������� ��������� �������� ���������� ������� (����� 1 - 8)
{
	// ������ ������� �� ����� 2 �� ����� 8
	Polygon(hdc, &ar_p[buf * 8 + 1], 7);	// ���������� ����� 1
}

int Arrows::calc2(unsigned int buf_N, int x1, int y1, int x2, int y2, unsigned short l, unsigned short w,
				  unsigned short s, unsigned short b, unsigned short L_fade)
{	// buf_N - ��������� ������ � ������ ���������
	// L_fade - ���� ������� � ��������, ������ ������� ��������������� ��������� ����� � ������ ���� (���� =0, �� ��
	// ���������)
	// w - ������ ���� ������� � ��������
	// s - ������ ������� � ��������
	// l - ����� ���� ������� � ��������
	// b - ��������� ���� ������� � ��������
	// ���� ��������:
	// 0 - ������ ���
	// 1 - ������� ��������� � �����

	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 == x2)
	{
		if (y2 == y1)			// ������� ��������������� ��������� ���������
		{
			// ������ �����? � �������� �� ���� ����� 1
			return 1;
		}
		else if (y2 > y1)
		{
			fix_r = M_PI_2;		// ������� ������ ����
		}
		else
		{
			fix_r = -M_PI_2;	// ������� ������ �����
		}
	}
	else
	{
		fix_r = atan2(dy, dx);
	}
	L = sqrt(dx * dx + dy * dy);
	if (L_fade > 0)		// ��������������� ��������� ������� ���� ������� ������� � ��������� ����������� ����� �������
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
	ar_p[buf_N].x = x1;												// ���������� � ����� 1
	ar_p[buf_N].y = y1;												// ���������� � ����� 1
	ar_p[buf_N + 1].x = x2;											// ���������� � ����� 2
	ar_p[buf_N + 1].y = y2;											// ���������� � ����� 2
	ar_p[buf_N + 2].x = (int)(x1 + round(x34Cos - ySin));			// ���������� � ����� 3
	ar_p[buf_N + 2].y = (int)(y1 + round(x34Sin + yCos));	        // ���������� � ����� 3
	ar_p[buf_N + 3].x = (int)(x1 + round(x78Cos - y5678Sin));		// ���������� � ����� 4
	ar_p[buf_N + 3].y = (int)(y1 + round(x78Sin + y5678Cos));		// ���������� � ����� 4
	ar_p[buf_N + 4].x = (int)(x1 + round(-y5678Sin));				// ���������� � ����� 5
	ar_p[buf_N + 4].y = (int)(y1 + round(y5678Cos));				// ���������� � ����� 5
	ar_p[buf_N + 5].x = (int)(x1 + round(y5678Sin));				// ���������� � ����� 6
	ar_p[buf_N + 5].y = (int)(y1 + round(-y5678Cos));				// ���������� � ����� 6
	ar_p[buf_N + 6].x = (int)(x1 + round(x78Cos + y5678Sin));	    // ���������� � ����� 7
	ar_p[buf_N + 6].y = (int)(y1 + round(x78Sin - y5678Cos));	    // ���������� � ����� 7
	ar_p[buf_N + 7].x = (int)(x1 + round(x34Cos + ySin));	        // ���������� � ����� 8
	ar_p[buf_N + 7].y = (int)(y1 + round(x34Sin - yCos));	        // ���������� � ����� 8

	return 0;
}
