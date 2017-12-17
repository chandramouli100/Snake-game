#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& board, const Snake & snake)
{
	Respawn(rng, board, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake & snake)
{
	std::uniform_int_distribution<int> DistX(0, brd.getWidth()-1 );
	std::uniform_int_distribution<int> DistY(0, brd.getHeight() - 1);

	do 
	{
		loc.x = DistX(rng);
		loc.y = DistY(rng);
	} while (snake.self_collision(loc));
}

void Goal::Draw(Board& board)
{
	board.DrawBlock(loc, c);
}

Location Goal::GetLocation() const
{
	return loc;
}
