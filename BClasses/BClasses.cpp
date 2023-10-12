// class_SelFrame.cpp : Определяет точку входа для приложения.
// v.0.6-12.10.23

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
unsigned char KeepAfterDrawing = { 1 };
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

//-\/ otladka
   // проверяем параметры объёмной стрелки  на корректность
   result = Arrow.test_2(60, 30, 60, 40); // возвращает 0 если параметры заданы корректно, 1...5 - если некорректно
//-/\ otladka

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
                break;
            case 32785: // Рисовать плоскую стрелку
                Arrow.mode.style = 1;
                break;
            case 32786: // Рисовать объёмную стрелку
                Arrow.mode.style = 2;
                break;
            case 32789: // Рисовать стрелку от ЛКМ
                Arrow.mode.type = 2;    //?
                Arrow.mode.button = 1;
                break;
            case 32790: // Рисовать стрелку от ПКМ
                Arrow.mode.type = 2;    //?
                Arrow.mode.button = 2;
                break;
            case 32791: // Рисовать стрелку от обеих КМ
                Arrow.mode.type = 2;    //?
                Arrow.mode.button = 3;
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
//            Arrow.mode.type = 2;    // рисуем стрелки при зажатой кнопкой мыши (ЛКМ или ПКМ)
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

        //if (message == WM_NCPAINT)
        //{
        //    int A = 1;
        //}

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
