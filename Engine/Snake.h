#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include<vector>

class Snake
{
private:
	class SnakeSeg
	{
	private:
		Location loc;
		Color c;
	public:
		SnakeSeg(const Location& loc, const Color c);
		void Follow(const SnakeSeg& seg);
		void Move(const Location& delta);
		void Draw(Board& board);
		const Location& GetLocation() const;
	};
	static constexpr Color Headcolor = Colors::Blue;
	static constexpr Color Bodycolor[3] = { {0, 255, 0}, {0, 200, 0}, {0,150,0} };
	std::vector<SnakeSeg> Segments;
	int seg_cur;
public:
	Snake(const Location& loc);
	void MoveSnake(const Location& delta);
	void GrowSnake();
	void Draw(Board& board);
	bool self_collision_without_last( const Location& loc ) const;
	bool self_collision( const Location& loc ) const;
	const Location GetNextHeadLocation(const Location& delta_loc) const;
};