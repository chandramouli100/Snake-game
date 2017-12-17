#pragma once

struct Location
{
	int x;
	int y;

	void Add(const Location& loc)
	{
		x += loc.x;
		y += loc.y;
	}
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};