#include "table.h"


Table::Table() : rowCount(5), columnCount(5), selectedCell(nullptr) 
{
	cells.resize(rowCount, vector<Cell>(columnCount));
}

void Table::layout(Size _size, Offset _offset)
{
	size = _size;
	offset = _offset;

	Size cellSize = Size(size.width / columnCount, size.height / rowCount);
	Offset cellOffset = offset;

	for (vector<Cell>& row : cells)
	{
		cellOffset.dx = offset.dx;
		for (Cell& cell : row)
		{
			cell.layout(cellSize, cellOffset);
			cellOffset.dx += cellSize.width;
		}
		cellOffset.dy += cellSize.height;
	}
}

void Table::paint(HDC hdc)
{
	for (vector<Cell>& row : cells)
	{
		for (Cell& cell : row)
		{
			cell.paint(hdc, &cell == selectedCell);
		}
	}
}

void Table::onMouseClick(Offset position)
{
	if (!size.contains(position - offset)) return;

	for (vector<Cell>& row : cells)
	{
		for (Cell& cell : row)
		{
			if (cell.hitTest(position))
			{
				selectedCell = &cell;
				return;
			}
		}
	}
}

void Table::onKeyPress(wchar_t character)
{
	if (selectedCell == nullptr) return;

	if (character == VK_LEFT) return resizeColumns(-1);
	if (character == VK_UP) return resizeRows(-1);
	if (character == VK_RIGHT) return resizeColumns(1);
	if (character == VK_DOWN) return resizeRows(1);
	
	if (character == '\b') return selectedCell->popCharacter();
	selectedCell->addCharacter(character);
}

void Table::resizeRows(int delta)
{
	rowCount = clampInt(rowCount + delta, ROW_MIN_COUNT, ROW_MAX_COUNT);

	cells.resize(rowCount, vector<Cell>(columnCount));

	layout(size, offset);
}

void Table::resizeColumns(int delta)
{
	columnCount = clampInt(columnCount + delta, COLUMN_MIN_COUNT, COLUMN_MAX_COUNT);

	for (vector<Cell>& row : cells)
	{
		row.resize(columnCount);
	}

	layout(size, offset);
}