#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Location.h"

class Board
{
private:
	static constexpr int dimension = 15;
	static constexpr int width = 30;
	static constexpr int height = 30;
	static constexpr int off_x = 50;
	static constexpr int off_y = 50;
	static constexpr Color c = Colors::Gray;
	Graphics& gfx;
public:
	Board(Graphics& gfx);
	void DrawBlock( const Location& loc, Color c);
	int getWidth() const;
	int getHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBoard(Graphics& gfx);
};