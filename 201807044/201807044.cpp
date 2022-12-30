// 201807044.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "201807044.h"


#define MAX_LOADSTRING 100
                                
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY201807044, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201807044));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201807044));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY201807044);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      700, 250, 1000, 1000, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
int i; 
int g_start; // 게임시작 및 새로고침
int g_score; // 점수 누적
int g_level; 
int g_time; // 시간

RECT g_item[10]; // 클릭해야될 동그라미

#define TIMER_ID_1      1      // 상대의 움직임을 위한 주기적인 호출 ID
#define TIMER_ID_2      2      // 제한 시간 타이머

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int can;
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_32771: //메뉴 게임시작
                MessageBox(hWnd, L"게임 시작합니다~~!!", L"게임시작", MB_OK);
                g_start = 1;
                g_time = 30;
                g_score = 0;

                SetTimer(hWnd, TIMER_ID_2, 1000, NULL); //시간종료후 메뉴를 다시 눌렀을때 타이머 재생성 및 호출
                g_level = 1000;
                SetTimer(hWnd, TIMER_ID_1, g_level, NULL);
                
                break;

            case ID_32772: { //메뉴 재시작
                int can = MessageBox(hWnd, L"게임 다시시작합니다~~!!", L"새로고침", MB_OKCANCEL);
                if (can == IDCANCEL) {
                }
                else {
                    g_start = 1;
                    g_time = 30;
                    g_score = 0;

                    SetTimer(hWnd, TIMER_ID_2, 1000, NULL); //시간종료후 메뉴를 다시 눌렀을때 타이머 재생성 및 호출
                    g_level = 1000;
                    SetTimer(hWnd, TIMER_ID_1, g_level, NULL);
                   
                    
                }
            }
            break;
                
               

                break;

            case ID_32773: { //메뉴 게임종료
                int can = MessageBox(hWnd, L"정말 그만하실껀가요???", L"게임종료", MB_OKCANCEL);
                if (can == IDCANCEL) {
                  
                }
                else
                    DestroyWindow(hWnd);
                }
                break;

            case ID_32774: //게임설명
                MessageBox(hWnd, L"              ★☆★순발력테스트 게임!!★☆★ \n   제한시간안에 최대한 많은 동그라미를 클릭해  \n           높은 점수를 얻는 사람이 승리하는 \n                   순발력 테스트 게임!! " ,L"게임설명", MB_OK);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN: {
        RECT mouse, is;  //IntersectRect함수 주소저장값 교차값주소저장 변수

        mouse.left = LOWORD(lParam); 
        mouse.top = HIWORD(lParam);
        mouse.right = mouse.left + 1;
        mouse.bottom = mouse.top + 1;

        if (g_start == 1) {
            for (i = 0; i < 10; i++) { //동그라미가 클릭되었을때 점수 추가 및 랜덤위치 재생성
                if (IntersectRect(&is, &mouse, &g_item[i])) 
                {
                    g_score += 10;

                    g_item[i].left = (rand() % 690) + 10;
                    g_item[i].top = (rand() % 820) + 20;
                    g_item[i].right = g_item[i].left + 50;
                    g_item[i].bottom = g_item[i].top + 50;
                }
     
            }

        }
    }
    break;
    
    case WM_CREATE:
    {   
         
            for (i = 0; i < 10; i++) { //동그라미 생성위치 및 크기 조절
                g_item[i].left = (rand() % 690) + 10;
                g_item[i].top = (rand() % 820) + 20;
                g_item[i].right = g_item[i].left + 50;
                g_item[i].bottom = g_item[i].top + 50;
                
            }
        

        g_time = 30; //게임시작시 제한시간 
        
        SetTimer(hWnd, TIMER_ID_2, 1000, NULL);

        g_level = 1000;
        // 타이머를 설정. 1초마다 주기적으로 호출
        // 설정한 시간마다 WM_TIMER 호출 -> OS에 요청
        SetTimer(hWnd, TIMER_ID_1, g_level, NULL);
        break;
        
    }
    break;

    case WM_TIMER:      // timer ID 값을 가지는 변수: 
    {
        if (TIMER_ID_2 == wParam && g_start == 1)   // 제한 시간 ID 값에 의한 주기적인 호출인지 확인
        {
            // 제한 시간 감소
            g_time--;

            // 제한 시간이 만료되면.
            if (0 == g_time)
            {
                // 게임 종료
                KillTimer(hWnd, TIMER_ID_1);
                KillTimer(hWnd, TIMER_ID_2);
                MessageBox(hWnd, L"  시간초과 게임끝!!", L"게임종료", MB_OK);
                return 0;
            }
            break;

        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    
    case WM_PAINT:
        {

        WCHAR string[64] = { 0, };
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            Rectangle(hdc, 10,910,750,30); //게임창
           
           
            wsprintf(string, L"Score: %d ", g_score);  // 점수 및 시간 나타냄
            TextOut(hdc, 800, 200, string, lstrlenW(string));
            wsprintf(string, L"Time: %d초", g_time);
            TextOut(hdc, 800, 250, string, lstrlenW(string));



            wsprintf(string, L"■□■ 게임 플레이방법 ■□■ ");
            TextOut(hdc, 760, 575, string, lstrlenW(string));
            wsprintf(string, L"왼쪽 상단의 게임시작을");
            TextOut(hdc, 780, 600, string, lstrlenW(string));
            wsprintf(string, L"눌러서 게임을 시작해주세요");
            TextOut(hdc, 770, 625, string, lstrlenW(string));

            wsprintf(string, L"★☆★ 점수 획득 방법★☆★");
            TextOut(hdc, 760, 675, string, lstrlenW(string));
            wsprintf(string, L"동그라미를 마우스 왼쪽");
            TextOut(hdc, 780, 700, string, lstrlenW(string));
            wsprintf(string, L"버튼을 클릭해 눌러서");
            TextOut(hdc, 790, 725, string, lstrlenW(string));
            wsprintf(string, L"점수를 획득하세요!!");
            TextOut(hdc, 790, 750, string, lstrlenW(string));

            if (g_start == 1) {
                for (i = 0; i < 10; i++) //동그라미 그리기
                {
                    Ellipse(hdc, g_item[i].left, g_item[i].top, g_item[i].right, g_item[i].bottom);

                }
                
             }

            EndPaint(hWnd, &ps);

            /*개선할 점 
            1. 시간초과후 재시작, 게임시작 해결       (o)
            2. 점수에 따른 레벨 시스템                (x)
            3. 클릭하면 점수가 깎이는 동그라미 만들기 (x)
            4.
            */
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

// 정보 대화 상자의 메시지 처리기입니다.
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
