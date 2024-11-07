#pragma once

#include "utils.h"
#include <wtypes.h>


constexpr POINT WINDOW_MIN_SIZE = POINT{ 300, 300 };
constexpr Offset TABLE_OFFSET = Offset(0, 0);

bool initWindow(HINSTANCE hInstance, int nCmdShow);

int runWindowMessageLoop();

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
