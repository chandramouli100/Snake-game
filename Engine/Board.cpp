#include "Board.h"
#include<assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}

void Board::DrawBlock(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);
	gfx.DrawRectDim(loc.x*dimension + off_x, loc.y*dimension + off_y, dimension, dimension, c);
}

int Board::getWidth() const
{
	return width;
}

int Board::getHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::DrawBoard(Graphics& gfx)
{
	//top line
	for ( int i = off_x; i < width*dimension - 1 + off_x; i++)
	{
		for ( int j = off_y; j < 3+off_y; j++)
		{
			gfx.PutPixel(i, j, c);
		}
	}
	
	//bottom line
	for (int i = off_x; i < width*dimension - 1 + off_x; i++)
	{
		for (int j = height*dimension - 1 + off_y; j > height*dimension - 4 + off_y; j--)
		{
			gfx.PutPixel(i, j, c);
		}
	}

	//left line
	for (int i = off_x; i < 3 + off_x; i++)
	{
		for (int j = off_y; j < height*dimension - 1 + off_y; j++)
		{
			gfx.PutPixel(i, j, c);
		}
	}

	//right line
	for (int i = width*dimension-1 + off_x; i > width*dimension-4 + off_x; i--)
	{
		for (int j = off_y; j < height*dimension - 1 + off_y; j++)
		{
			gfx.PutPixel(i, j, c);
		}
	}
}
