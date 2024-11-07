#include "cell.h"


Cell::Cell() : textBoundsRect{0, 0, 0, 0} {}

void Cell::layout(Size _size, Offset _offset)
{
    size = _size;
    offset = _offset;

    textBoundsRect.left = offset.dx + TEXT_PADDING;
    textBoundsRect.top = offset.dy + TEXT_PADDING;
    textBoundsRect.right = offset.dx + size.width - TEXT_PADDING;
    textBoundsRect.bottom = offset.dy + size.height - TEXT_PADDING;
}

void Cell::paint(HDC hdc, bool isSelected)
{
    drawRect(hdc, isSelected);
    drawText(hdc);
}

bool Cell::hitTest(Offset position)
{
    return size.contains(position - offset);
}

void Cell::addCharacter(wchar_t character)
{
    if (text.size() >= CELL_TEXT_MAX_LENGTH) return;

    text.push_back(character);
}

void Cell::popCharacter()
{
    if (text.empty()) return;

    text.pop_back();
}

void Cell::drawRect(HDC hdc, bool isSelected)
{
    HBRUSH hBrush = CreateSolidBrush(isSelected ? blueColor : whiteColor);
    HPEN hPen = CreatePen(PS_SOLID, 2, blackColor);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);

    Rectangle(
        hdc,
        offset.dx,
        offset.dy,
        offset.dx + size.width,
        offset.dy + size.height
    );

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Cell::drawText(HDC hdc)
{
    if (text.empty()) return;

    int fontSize = CELL_TEXT_MAX_FONT_SIZE;

    while (fontSize >= CELL_TEXT_MIN_FONT_SIZE)
    {
        HFONT hFont = createFont(fontSize);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        RECT textRect = textBoundsRect;
        DrawTextW(hdc, text.c_str(), -1, &textRect, DT_WORDBREAK | DT_CALCRECT);

        if (isRectWithinBounds(textRect, textBoundsRect))
        {
            int oldBkMode = SetBkMode(hdc, TRANSPARENT);

            DrawTextW(hdc, text.c_str(), -1, &textBoundsRect, DT_WORDBREAK);

            fontSize = CELL_TEXT_MIN_FONT_SIZE;
            SetBkMode(hdc, oldBkMode);
        }

        fontSize -= CELL_TEXT_FONT_SIZE_STEP;
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
    }
}