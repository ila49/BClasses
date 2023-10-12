// v.0.2-12.10.23

#pragma once
#include <math.h>
#include <corecrt_math_defines.h>
#include <Windows.h>
#include <vector>
#include "SelFrame.h"

class Arrows
{
	double alf_r, fix_r, dx, dy, L, Sin, Cos, x34, x78, y, y5678, x34Cos, x78Cos, ySin, y5678Sin, x34Sin, x78Sin, yCos,
		   y5678Cos, K;
	POINT Point;
	int buf_N;
	unsigned int buf_i;

public:
	struct Mode
	{
		short type;
		short button;
		short style;
	} mode;
	POINT p[8];
	int res;
	std::vector<POINT> ar_p;
	Arrows(); // конструктор класса
	// расчёт параметров простой стрелки
	int calc_1(unsigned int, int, int, int, int, unsigned short, unsigned short, unsigned short);
	// отрисовка простой стрелки
	void draw_1(HDC, POINT*);
	// проверка на корректность параметров объёмной стрелки
	int test_2(unsigned short l, unsigned short w, unsigned short s, unsigned short b);
	// расчёт параметров объёмной стрелки
	int calc_2(unsigned int, int, int, int, int, unsigned short, unsigned short, unsigned short,
			   unsigned short, unsigned short);
	// отрисовка объёмной стрелки
	void draw_2(HDC, unsigned int);
	int wm_paint(HDC, SelFrame*, int*, unsigned int, unsigned short, unsigned short,
		         unsigned short, unsigned short, unsigned short);
	void draw1(HDC, unsigned int);
	void draw2(HDC, unsigned int);
	int calc2(unsigned int, int, int, int, int, unsigned short, unsigned short, unsigned short,
		unsigned short, unsigned short);
};

