#pragma once

#include "utils.h"
#include <wtypes.h>
#include <string>


constexpr int CELL_TEXT_FONT_SIZE_STEP = 2;
constexpr int CELL_TEXT_MAX_FONT_SIZE = 80;
constexpr int CELL_TEXT_MIN_FONT_SIZE = 10;
constexpr int CELL_TEXT_MAX_LENGTH = 100;
constexpr int TEXT_PADDING = 10;

constexpr COLORREF blackColor = RGB(0, 0, 0);
constexpr COLORREF blueColor = RGB(173, 216, 230);
constexpr COLORREF whiteColor = RGB(255, 255, 255);

using namespace std;

class Cell  {
public:
	Cell();

	void layout(Size _size, Offset _offset);
	void paint(HDC hdc, bool isSelected);
	bool hitTest(Offset position);
	void addCharacter(wchar_t c);
	void popCharacter();

private:
	Size size;
	Offset offset;
	wstring text;
	RECT textBoundsRect;

	void drawRect(HDC hdc, bool isSelected);
	void drawText(HDC hdc);
};