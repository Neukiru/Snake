#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Goal
{
public:

	class Boulder
	{
	public:
		void InitBoulder(std::mt19937& rng, const Board& brd, const Snake& snake);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;

	private:
		Location loc;
		Color c = Colors::LightGray;
	};

	Goal(std::mt19937& rng, const Board& brd, const Snake& snake, Goal& otherObject);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, Goal& otherObject,const Goal::Boulder& otherObject2);
	void Draw(Board& brd, Color c) const;
	const Location& GetLocation() const;
	
private:
	Location loc;
};
