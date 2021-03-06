﻿//pr2Dgame_01.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//3월 27일 : 2d 게임 제작을 체험해보자!

#include "stdafx.h"
#include "pr2Dgame_01.h"
#include "graphic.h"
#include "debug.h"
#include "FrameWork.h"

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//게임 장면 크기 지정
#define WIDTH  800//윈도우 가로
#define HEIGHT 224//윈도우 세로

//메크로 함수(#define) 테스트 하기 : 일반함수보다 빠르다.
#define TEST(X) printf("%d",X); 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
	//디버그콘솔창 띄우기
	START_DEBUG_CONSOLE();
	printf("디버그 콘솔 열기");
	TEST(100);
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PR2DGAME01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PR2DGAME01));

	MSG msg = {0};//모든요소를 0으로 초기화

	//프레임 워크 객체 가져오기
	FrameWork * frameWork = FrameWork::instance();

	frameWork->init(hWnd,WIDTH,HEIGHT);

    // 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
	while (msg.message!=WM_QUIT)//종료가 나오기 전까지 실행된다.//true
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			//윈도우에 구애받지 않고 메세지를 모두 가져옴,최소값과 최대값을 구분없이 가져오기 위해서 0을 씀
		{
		
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		//게임 구동
		frameWork->run();
		
    }

	//게임 종료
	frameWork->exit();

	//디버그 콘솔창 닫기
	STOP_DEBUG_CONSOLE();
    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PR2DGAME01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PR2DGAME01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;// | WS_MAXIMIZEBOX;// , CW_USEDEFAULT
   //윈도우 크기지정////////////////////////////////////////////////////////////
   RECT rt = { 0,0,WIDTH,HEIGHT };

   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);//윈도우 크기계산

   int width	= rt.right - rt.left;//윈도우 가로
   int height	= rt.bottom - rt.top;//윈도우 세로
   
   //윈도우 위치 조정하기
   int scrWidth = GetSystemMetrics(SM_CXSCREEN);//모니터 가로 해상도 구하기
   int wndX = (scrWidth - WIDTH) / 2;//윈도우의 x좌표
   int wndY = 150;//윈도우의 x좌표
   hWnd = CreateWindowW(szWindowClass, //지역변수를 전역으로 바꿈
								szTitle, 
								style,		
								wndX,//윈도우x
								wndY,//윈도우Y좌표 
								width,//윈도우 가로
								height,//윈도우 세로
								nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			render();//화면 실시간 렌더링
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


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
