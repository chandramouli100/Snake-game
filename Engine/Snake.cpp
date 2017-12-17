#pragma once

#include "Snake.h"
#include<iostream>
#include<assert.h>
#include<math.h>

Snake::Snake(const Location & loc)
	:
	Segments(),
	seg_cur(1)
{
	Segments.push_back(SnakeSeg(loc, Headcolor));
}

void Snake::MoveSnake(const Location& delta)
{
	//moving body of the snake
	for (int i = seg_cur - 1; i > 0; i--)
	{
		Segments[i].Follow(Segments[i - 1]);
	}
	//moving head of the snake
	Segments[0].Move(delta);
}

void Snake::GrowSnake()
{
	Segments.push_back(SnakeSeg({}, Bodycolor[seg_cur%3]));
	seg_cur++;
}

void Snake::Draw(Board & board)
{
	for (int i = 0; i < seg_cur; i++)
		Segments[i].Draw(board);
}

bool Snake::self_collision_without_last(const Location& loc) const
{
	for (int i = 0; i < seg_cur-1; i++)
	{
		if (loc == Segments[i].GetLocation())
			return true;
	}
	return false;
}

bool Snake::self_collision(const Location& loc) const
{
	for (int i = 0; i < seg_cur; i++)
	{
		if ( loc == Segments[i].GetLocation())
			return true;
	}
	return false;
}

const Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location cur_location(Segments[0].GetLocation());
	cur_location.Add(delta_loc);
	return cur_location;
}

Snake::SnakeSeg::SnakeSeg(const Location& in_loc, Color in_c)
	:
	loc(in_loc),
	c(in_c)
{
}

void Snake::SnakeSeg::Follow(const SnakeSeg & seg)
{
	loc = seg.loc;
}

void Snake::SnakeSeg::Move(const Location& delta)
{
	assert(abs(delta.x) + abs(delta.y) == 1);
	loc.Add(delta);
}

void Snake::SnakeSeg::Draw(Board & board)
{
	board.DrawBlock(loc, c);
}

const Location& Snake::SnakeSeg::GetLocation() const
{
	return loc;
}
