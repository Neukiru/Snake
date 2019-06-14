#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake, Goal& otherObject)
{
	//Respawn(rng, brd, snake, otherObject);
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || newLoc == otherObject.loc);
	loc = newLoc;
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, Goal& otherObject,const Goal::Boulder& otherObject2)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || newLoc== otherObject.loc || newLoc == otherObject2.GetLocation());
	loc = newLoc;
}


void Goal::Draw(Board& brd, Color c) const
{
	brd.DrawCell(loc, c);
}

const Location& Goal::GetLocation() const
{
	return loc;
}

void Goal::Boulder::InitBoulder(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::Boulder::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Goal::Boulder::GetLocation() const
{
	return loc;
}
