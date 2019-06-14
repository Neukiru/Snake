#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int offsetX = x+BorderWidth;
	const int offsetY = y+ BorderWidth;

	gfx.DrawRectangleDim(loc.x * dimension+offsetX+SpaceBtwnCells, loc.y * dimension+offsetY+SpaceBtwnCells,dimension-SpaceBtwnCells*2,dimension-SpaceBtwnCells*2,c);
	//afusfhoaw
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x>=0 && loc.x<width &&
		loc.y >=0 && loc.y<height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top+BorderWidth*2+height*dimension;
	const int right=left + BorderWidth * 2 + width * dimension;

	gfx.DrawRectangle(left,top,right,top+BorderWidth,borderC);
	gfx.DrawRectangle(left, top + BorderWidth, left + BorderWidth, bottom - BorderWidth, borderC);
	gfx.DrawRectangle(left, bottom - BorderWidth, right, bottom, borderC);
	gfx.DrawRectangle(right - BorderWidth, top + BorderWidth, right, bottom - BorderWidth, borderC);
}
