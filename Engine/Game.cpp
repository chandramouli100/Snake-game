/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include<random>
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(std::random_device()()),
	snake({ 5, 5 }),
	delta_loc({ 1, 0 }),
	snakeMoveCounter(0),
	snakeMovePeriod(10),
	goal(rng, board, snake),
	cur_dir('r'),
	eaten_so_far(0),
	speedUpPeriod(4),
	next_dir()
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!GameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if (cur_dir != 'd')
			{
				delta_loc = { 0, -1 };
				next_dir = 'u';
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (cur_dir != 'u')
			{
				delta_loc = { 0, 1 };
				next_dir = 'd';
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (cur_dir != 'r')
			{
				delta_loc = { -1, 0 };
				next_dir = 'l';
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (cur_dir != 'l')
			{
				delta_loc = { 1, 0 };
				next_dir = 'r';
			}
		}

		//moving the snake
		snakeMoveCounter++;
		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter = 0;
			Location next_head = snake.GetNextHeadLocation(delta_loc);
			if (snake.self_collision_without_last(next_head) || !board.IsInsideBoard(next_head))
				GameOver = true;
			else
			{
				const bool eating = (next_head == goal.GetLocation());
				if (eating)
				{
					snake.GrowSnake();
					eaten_so_far++;
				}
				
				snake.MoveSnake(delta_loc);
				
				if (eating)
				{
					goal.Respawn(rng, board, snake);

					//speeding up the snake movement
					if (eaten_so_far >= speedUpPeriod)
					{
						eaten_so_far = 0;
						speedUpPeriod = speedUpPeriod / 2;
						if (snakeMovePeriod > 3)
							snakeMovePeriod--;
					}
				}

				//changing direction reference
				cur_dir = next_dir;
			}
		}
	}
}

void Game::ComposeFrame()
{
	snake.Draw(board);
	goal.Draw(board);
	board.DrawBoard(gfx);

	if(GameOver)
	{
		SpriteCodex::DrawGameOver(100, 100, gfx);
	}
}
