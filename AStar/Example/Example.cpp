// Example.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Example.h"
#include "TileMap.h"
#include "../AStar/AStarTile.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

CTileMap g_Map;
CAStarTile g_AStar;

POINT g_Start;
POINT g_End;

HBRUSH g_GreenBrush;
HBRUSH g_BlueBrush;
HBRUSH g_RedBrush;

// �˴���ģ���а����ĺ�����ǰ������: 
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

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXAMPLE));

    MSG msg;

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXAMPLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION| WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   LOGBRUSH logBrush;
   logBrush.lbColor = RGB(0, 0, 255);
   logBrush.lbHatch = HS_CROSS;
   logBrush.lbStyle = BS_SOLID;
   g_GreenBrush = CreateBrushIndirect(&logBrush);
   logBrush.lbColor = RGB(0, 255, 0);
   g_BlueBrush = CreateBrushIndirect(&logBrush);
   logBrush.lbColor = RGB(255, 0, 0);
   g_RedBrush = CreateBrushIndirect(&logBrush);

   int nSize = 600;

   g_Map.Init(nSize, nSize, 600/ nSize);
   g_AStar.Init(g_Map.GetWidth(), g_Map.GetHeight(), true);

   g_Start.x = 0;
   g_Start.y = 0;


   g_End.x = g_Map.GetWidth()-1;
   g_End.y = g_Map.GetHeight()-1;

   srand(GetTickCount());
   auto &tiles = g_AStar.GetTileNode();

   //for (int i = 3; i < 31; i++)
   //{
   //    tiles[i].loss = -1;
   //}

   for (int i = 0; i < tiles.size(); i++)
   {
	   tiles[i].loss = rand() % 3 == 0 ? -1 : 10;
   }
   tiles[0].loss = 10;
   tiles[tiles.size()-1].loss = 10;
   g_AStar.Search(g_Start.x, g_Start.y, g_End.x, g_End.y);
   RECT rc = {0, 0, g_Map.GetWidth()*g_Map.GetCellSize(), g_Map.GetHeight()*g_Map.GetCellSize() };
   AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), true);
   SetWindowPos(hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
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
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
			g_Map.DrawMap(hdc);
			
			auto tiles = g_AStar.GetTileNode();
			for (int i = 0; i < tiles.size(); i++)
			{
				auto &tile = tiles[i];
				if (tile.loss == -1)
				{
					g_Map.DrawTile(hdc, tile.index, g_BlueBrush);
				}
			}

			auto listPath = g_AStar.GetPath();
			for (auto itr = listPath.begin(); itr != listPath.end(); ++itr)
			{
				int nIndex = ((CAStarTileNode*)(*itr))->index;
				g_Map.DrawTile(hdc, nIndex, g_GreenBrush);
			}
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		g_Start.x = xPos / g_Map.GetCellSize();
		g_Start.y = yPos / g_Map.GetCellSize();
		DWORD dwTime = GetTickCount();
		g_AStar.Search(g_Start.x, g_Start.y, g_End.x, g_End.y);
		char szTemp[100];
		sprintf(szTemp, "%d\n", GetTickCount() - dwTime);
		OutputDebugStringA(szTemp);

		InvalidateRect(hWnd, NULL, false);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		g_End.x = xPos / g_Map.GetCellSize();
		g_End.y = yPos / g_Map.GetCellSize();

		DWORD dwTime = GetTickCount();
		g_AStar.Search(g_Start.x, g_Start.y, g_End.x, g_End.y);
		char szTemp[100];
		sprintf(szTemp, "%d\n", GetTickCount() - dwTime);
		OutputDebugStringA(szTemp);
		InvalidateRect(hWnd, NULL, false);
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

// �����ڡ������Ϣ�������
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
