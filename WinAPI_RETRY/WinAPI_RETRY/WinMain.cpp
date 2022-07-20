#include "framework.h"

HWND hWindow = 0;

LRESULT CALLBACK WndProc(HWND hWindow, UINT uMessage, WPARAM wParameter, LPARAM lParameter);

int WINAPI WinMain(
		HINSTANCE hInstance	,
		HINSTANCE hPrevInstance,
		PSTR	  pCmdLine		,
		int		  nShowCmd		)
{

	{
		WNDCLASSEX wndClass = WNDCLASSEX();

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.lpfnWndProc = WndProc;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.lpszClassName = L"Window";
		wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wndClass);
	}

	{
		CREATESTRUCT window = CREATESTRUCT();

		window.lpszClass = L"Window";
		window.lpszName = L"Game";
		window.style = WS_CAPTION | WS_SYSMENU;
		window.cx = CW_USEDEFAULT;
		window.cy = CW_USEDEFAULT;
		window.hInstance = hInstance;

		{
			RECT rect = RECT();
			rect.right = window.cx;
			rect.bottom = window.cy;

			AdjustWindowRectEx(&rect, window.style, static_cast<bool>(window.hMenu), window.dwExStyle);
			window.cx = rect.right - rect.left;
			window.cy = rect.bottom - rect.top;

			window.x = (GetSystemMetrics(SM_CXSCREEN) - window.cx) / 2;
			window.y = (GetSystemMetrics(SM_CYSCREEN) - window.cy) / 2;
		}

		hWindow = CreateWindowEx
		(
			window.dwExStyle,  window.lpszClass,
			window.lpszName,   window.style,
			CW_USEDEFAULT,     CW_USEDEFAULT,
			CW_USEDEFAULT,     CW_USEDEFAULT,
			window.hwndParent, window.hMenu,
			window.hInstance,  window.lpCreateParams
		);

		ShowWindow(hWindow, SW_RESTORE);
	}

	{
		MSG msg = { 0 };

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					return (int)msg.wParam;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				SendMessage(hWindow, WM_APP, 0, 0);
			}
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello,World", L"Hello", MB_OK);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWindow);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}