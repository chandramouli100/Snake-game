#pragma once

#include "Location.h"
#include "Colors.h"
#include "Snake.h"
#include "Board.h"
#include<random>

class Goal
{
private:
	Location loc;
	static constexpr Color c = Colors::Red;
	std::mt19937 rng;
public:
	Goal(std::mt19937& rng, const Board& board, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& board, const Snake& snake);
	void Draw(Board& board);
	Location GetLocation() const;
};