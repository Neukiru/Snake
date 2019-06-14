#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
private:
	static constexpr Color borderC = {136,136,210};
	static constexpr int dimension = 18;
	static constexpr int SpaceBtwnCells = 1;
	static constexpr int width=36;
	static constexpr int height=27;
	static constexpr int BorderWidth = 4;

	static constexpr int x = 70;
	static constexpr int y = 50;
	Graphics& gfx;
};