#pragma once

#include "utils.h"
#include "cell.h"
#include <vector>


constexpr int ROW_MAX_COUNT = 10;
constexpr int ROW_MIN_COUNT = 1;
constexpr int COLUMN_MAX_COUNT = 10;
constexpr int COLUMN_MIN_COUNT = 1;

using namespace std;

class Table {
public:
	Table();

	void layout(Size _size, Offset _offset);
	void paint(HDC hdc);
	void onMouseClick(Offset position);
	void onKeyPress(wchar_t character);

private:
	Size size;
	Offset offset;
	Cell* selectedCell;
	int rowCount, columnCount;
	vector<vector<Cell>> cells;

	void resizeRows(int delta);
	void resizeColumns(int delta);
};