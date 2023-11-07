// class_SelFrame.cpp : Определяет точку входа для приложения.
// v.0.7-07.11.23

#include "framework.h"
#include "BClasses.h"
#include "Arrows.h"
//import "BClasses.h";                          // тест на С++20

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int result;
HMENU hmenu;
DWORD dw;
long Checked, Unchecked;

//// Создаем единственный объект класса AntiFlicker
AntiFlicker AF;
//// Создаем единственный объект класса SelFrame
SelFrame SF;
SelFrame* pSF = &SF;
//// Создаем единственный объект класса Arrows
Arrows Arrow;   // Пока дезактивирован

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLASSSELFRAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLASSSELFRAME));

    //-\/ test
    int* one_two_three{ new int[] {1, 2, 3} };      // тест на С++20
    int ONE = *one_two_three;
    int TWO = *(one_two_three + 1);
    int THREE = *(one_two_three + 2);
    int One = one_two_three[0];
    int Two = one_two_three[1];
    int Three = one_two_three[2];
    delete[] one_two_three;
    one_two_three = nullptr;
    //-/\ test

    // начало первоначальной настройки меню
    hmenu = GetMenu(SF.hw);
    Checked = MF_BYCOMMAND | MF_CHECKED;
    Unchecked = MF_BYCOMMAND | MF_UNCHECKED;
    if (Arrow.mode.type == 0 || Arrow.mode.button == 0) dw = CheckMenuItem(hmenu, ID_32784, Checked);
    else dw = CheckMenuItem(hmenu, ID_32784, Unchecked);
    // Стрелки -> Рисовать -> От ЛКМ
    if (Arrow.mode.type == 2 || Arrow.mode.button == 1) dw = CheckMenuItem(hmenu, ID_32789, Checked);
    else dw = CheckMenuItem(hmenu, ID_32789, Unchecked);
    // Стрелки -> Рисовать -> От ПКМ
    if (Arrow.mode.type == 2 || Arrow.mode.button == 2) dw = CheckMenuItem(hmenu, ID_32790, Checked);
    else dw = CheckMenuItem(hmenu, ID_32790, Unchecked);
    // Стрелки -> Рисовать -> От обеих КМ
    if (Arrow.mode.type == 2 || Arrow.mode.button == 3) dw = CheckMenuItem(hmenu, ID_32791, Checked);
    else dw = CheckMenuItem(hmenu, ID_32791, Unchecked);
    // Стрелки -> Плоские
    if (Arrow.mode.style == 1) dw = CheckMenuItem(hmenu, ID_32785, Checked);
    else dw = CheckMenuItem(hmenu, ID_32785, Unchecked);
    // Стрелки -> Объёмные
    if (Arrow.mode.style == 2) dw = CheckMenuItem(hmenu, ID_32786, Checked);
    else dw = CheckMenuItem(hmenu, ID_32786, Unchecked);
    // Стрелки -> Режим А -> Обе КМ
    if (Arrow.mode.type2_LB == 0 && Arrow.mode.type2_RB == 0) dw = CheckMenuItem(hmenu, ID_32794, Checked);
    else
    {
        dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
        // Стрелки -> Режим А -> ЛКМ
        if (Arrow.mode.type2_LB == 0) dw = CheckMenuItem(hmenu, ID_32795, Checked);
        else dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
        // Стрелки -> Режим А -> ПКМ
        if (Arrow.mode.type2_RB == 0) dw = CheckMenuItem(hmenu, ID_32796, Checked);
        else dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
    }
    // Стрелки -> Режим Б -> Обе КМ
    if (Arrow.mode.type2_LB == 1 && Arrow.mode.type2_RB == 1) dw = CheckMenuItem(hmenu, ID_32797, Checked);
    else
    {
        dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
        // Стрелки -> Режим Б -> ЛКМ
        if (Arrow.mode.type2_LB == 1) dw = CheckMenuItem(hmenu, ID_32798, Checked);
        else dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
        // Стрелки -> Режим Б -> ПКМ
        if (Arrow.mode.type2_RB == 1) dw = CheckMenuItem(hmenu, ID_32799, Checked);
        else dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
    }
    // Стрелки -> Режим В -> Обе КМ
    if (Arrow.mode.type2_LB == 2 && Arrow.mode.type2_RB == 2) dw = CheckMenuItem(hmenu, ID_32801, Checked);
    else
    {
        dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
        // Стрелки -> Режим В -> ЛКМ
        if (Arrow.mode.type2_LB == 2) dw = CheckMenuItem(hmenu, ID_32802, Checked);
        else dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
        // Стрелки -> Режим В -> ПКМ
        if (Arrow.mode.type2_RB == 2) dw = CheckMenuItem(hmenu, ID_32803, Checked);
        else dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
    }
    // конец первоначальной настройки меню

    MSG msg;
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLASSSELFRAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLASSSELFRAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // | WS_BORDER,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   SF.init(hWnd, pSF);   // инициируем объект

//*\/ otladka
   // проверяем параметры объёмной стрелки  на корректность
   result = Arrow.test_2(60, 30, 60, 40); // возвращает 0 если параметры заданы корректно, 1...5 - если некорректно
//*/\ otladka

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_LBUTTONDOWN:
        {
            SF.wm_lbuttondown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;

    case WM_LBUTTONUP:
        {
            SF.wm_lbuttonup(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;

    case WM_RBUTTONDOWN:
        {
            SF.wm_rbuttondown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;

    case WM_RBUTTONUP:
        {
            SF.wm_rbuttonup(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;

    case WM_MOUSEMOVE:
        {
            SF.wm_mousemove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;

    case WM_MOUSELEAVE:
        {
            SF.wm_mouseleave();
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case 32772: // ЛКМ: слежение и отрисовка 
                SF.SetMode(-3);
                break;
            case 32773: // ЛКМ: только слежение 
                SF.SetMode(-2);
                break;
            case 32774: // ЛКМ: не работает 
                SF.SetMode(-4);
                break;
            case 32776: // ПКМ: слежение и отрисовка 
                SF.SetMode(3);
                break;
            case 32777: // ПКМ: только слежение 
                SF.SetMode(2);
                break;
            case 32778: // ПКМ: не работает 
                SF.SetMode(4);
                break;
            case 32780: // Обе КМ: слежение и отрисовка 
                SF.SetMode(1);
                break;
            case 32781: // Обе КМ: только слежение
                SF.SetMode(-1);
                break;
            case 32782: // Обе КМ: не работают
                SF.SetMode(0);
                break;
            //case 32783: // Рисовать стрелки
            //    Arrow.mode.type = 2;
            //    break;
            case 32784: // Не рисовать стрелки
                Arrow.mode.type = 0;
                dw = CheckMenuItem(hmenu, ID_32784, Checked);
                dw = CheckMenuItem(hmenu, ID_32789, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32790, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32791, Unchecked);
                break;
            case 32785: // Рисовать плоскую стрелку
                Arrow.mode.style = 1;
                dw = CheckMenuItem(hmenu, ID_32785, Checked);
                dw = CheckMenuItem(hmenu, ID_32786, Unchecked);
                break;
            case 32786: // Рисовать объёмную стрелку
                Arrow.mode.style = 2;
                dw = CheckMenuItem(hmenu, ID_32786, Checked);
                dw = CheckMenuItem(hmenu, ID_32785, Unchecked);
                break;
            case 32789: // Рисовать стрелку от ЛКМ
                Arrow.mode.type = 2;
                Arrow.mode.button = 1;
                dw = CheckMenuItem(hmenu, ID_32789, Checked);
                dw = CheckMenuItem(hmenu, ID_32784, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32790, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32791, Unchecked);
                break;
            case 32790: // Рисовать стрелку от ПКМ
                Arrow.mode.type = 2;
                Arrow.mode.button = 2;
                dw = CheckMenuItem(hmenu, ID_32790, Checked);
                dw = CheckMenuItem(hmenu, ID_32784, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32789, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32791, Unchecked);
                break;
            case 32791: // Рисовать стрелки от обеих КМ
                Arrow.mode.type = 2;
                Arrow.mode.button = 3;
                dw = CheckMenuItem(hmenu, ID_32791, Checked);
                dw = CheckMenuItem(hmenu, ID_32784, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32789, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32790, Unchecked);
                break;
            case 32794: // Режим А для обеих КМ
                Arrow.mode.type2_LB = 0;
                Arrow.mode.type2_RB = 0;
                dw = CheckMenuItem(hmenu, ID_32794, Checked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                // деактивировать всё в режиме Б и В
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32795: // Режим А для ЛКМ
                Arrow.mode.type2_LB = 0;
                dw = CheckMenuItem(hmenu, ID_32795, Checked);
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                // деактивировать всё в режиме Б и В
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32796: // Режим А для ЛКМ
                Arrow.mode.type2_LB = 0;
                dw = CheckMenuItem(hmenu, ID_32796, Checked);
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                // деактивировать всё в режиме Б и В
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32797: // Режим Б для обеих КМ
                Arrow.mode.type2_LB = 1;
                Arrow.mode.type2_RB = 1;
                dw = CheckMenuItem(hmenu, ID_32797, Checked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                // деактивировать всё в режиме А и В
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32798: // Режим Б для ЛКМ
                Arrow.mode.type2_LB = 1;
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Checked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                // деактивировать всё в режиме А и В
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32799: // Режим Б для ПКМ
                Arrow.mode.type2_RB = 1;
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Checked);
                // деактивировать всё в режиме А и В
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                break;
            case 32801: // Режим В для обеих КМ
                Arrow.mode.type2_LB = 2;
                Arrow.mode.type2_RB = 2;
                dw = CheckMenuItem(hmenu, ID_32801, Checked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                // деактивировать всё в режиме А и Б
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                break;
            case 32802: // Режим В для ЛКМ
                Arrow.mode.type2_LB = 2;
                dw = CheckMenuItem(hmenu, ID_32802, Checked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32803, Unchecked);
                // деактивировать всё в режиме А и Б
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                break;
            case 32803: // Режим В для ПКМ
                Arrow.mode.type2_RB = 2;
                dw = CheckMenuItem(hmenu, ID_32803, Checked);
                dw = CheckMenuItem(hmenu, ID_32801, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32802, Unchecked);
                // деактивировать всё в режиме А и Б
                dw = CheckMenuItem(hmenu, ID_32794, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32795, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32796, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32797, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32798, Unchecked);
                dw = CheckMenuItem(hmenu, ID_32799, Unchecked);
                break;

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            AF.wm_paint_0(hWnd, hdc, (HBRUSH)(COLOR_WINDOW + 1));   // выполняется сразу после BeginPaint
            SF.wm_paint(AF.memDC);




            // установить цвет и тип линий для рисования объёмной стрелки
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255)); // цвет заливки - синий
            SelectObject(AF.memDC, brush);
            HPEN pen = CreatePen(PS_SOLID,				     // непрерывная линия
                                 0,						     // толщина рамки - 1 пиксел
                                 RGB(0, 0, 255));		     // цвет рамки - синий
            SelectObject(AF.memDC, pen);

            // с какими буферами работаем в случае mode=1
            int pool[3] = { 2,2,-3 };  // управляющий массив буферов: использовать данные из 2 буферов (первый элемент),
                                       // их номера: 2 и 3 (остальные элементы);
                                       // 
//            Arrow.mode.type = 0;    // не рисуем стрелки
//            Arrow.mode.type = 1;    // рисуем стрелки из буферов (для этого передаём управляющий массив pool)
//            Arrow.mode.type = 2;    // рисуем стрелки при зажатой кнопке мыши (ЛКМ или ПКМ)
//            Arrow.mode.button = 1;  // рисуем от ЛКМ
//            Arrow.mode.button = 2;  // рисуем от ПКМ
//            Arrow.mode.type = 2;

            result = Arrow.wm_paint(AF.memDC,
                                    pSF,      // указатель на объект SF
                                    pool,     // указатель на массив типа int (управляющий массив буферов) для mode.type=1
                                    1,        // если mode.type=2, буфер, в который сохраняются рассчитанные параметры стрелки
                                    60,       // l - длина усов стрелки в пикселах 
                                    60,       // w - ширина усов стрелки в пикселах      
                                    10,       // s - ширина стрелки в пикселах (для объёмной стрелки)       
                                    40,       // b - основание усов стрелки в пикселах (для объёмной стрелки)
                                    200       // L_fade - длина стрелки в пикселах, меньше которой пропроцилнально уменьшать длину
                                    );        //  и ширину усов (если =0, то не уменьшать)

            AF.wm_paint_1(hdc);               // выполняется непосредственно перед EndPaint
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_ERASEBKGND:
        return 1;
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    //case WM_NCPAINT:
    //    if (SF.DoNotRedrawNC)
    //    {
    //        SF.DoNotRedrawNC = FALSE;
    //    }
    //    else
    //    {
    //        return DefWindowProc(hWnd, message, wParam, lParam);
    //    }
    //    break;


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
