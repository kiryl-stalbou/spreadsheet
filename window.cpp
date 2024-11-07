#include "table.h"
#include "window.h"
#include "Resource.h"
#include <windowsx.h>


Table table;

bool initWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEXW wcexw;

    wcexw.cbSize = sizeof(WNDCLASSEX);

    wcexw.cbClsExtra = 0;
    wcexw.cbWndExtra = 0;
    wcexw.lpfnWndProc = wndProc;
    wcexw.lpszMenuName = nullptr;
    wcexw.hInstance = hInstance;
    wcexw.lpszClassName = L"Table_Class";
    wcexw.style = CS_HREDRAW | CS_VREDRAW;
    wcexw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcexw.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcexw.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TABLE));
    wcexw.hIconSm = LoadIcon(wcexw.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcexw);

    HWND hWnd = CreateWindowW(
        L"Table_Class", L"Table", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) return false;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return true;
}

int runWindowMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_GETMINMAXINFO:
        {
            MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
            pInfo->ptMinTrackSize = WINDOW_MIN_SIZE;
            break;
        }
        case WM_SIZE:
        {
            Size size = Size(LOWORD(lParam) - TABLE_OFFSET.dx, HIWORD(lParam) - TABLE_OFFSET.dy);
            table.layout(size, TABLE_OFFSET);
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            table.paint(hdc);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            Offset position = Offset(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            table.onMouseClick(position);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        }
        case WM_KEYDOWN:
        {
            table.onKeyPress(wParam);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}