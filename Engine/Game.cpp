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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	shnek({2,2}),
	apple(rng,brd,shnek,FakeApple),
	FakeApple(rng,brd,shnek, apple)
{
	for (int i = 0; i < BouldersMax; ++i)
	{
		boulders[i].InitBoulder(rng, brd, shnek);
	}
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
	if (GameIsStarted && !GameIsOver)
	{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1,0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1,0 };
			}

			++shnekMoveCounter;
			if (shnekMoveCounter >= shnekMovePeriod)
			{
				shnekMoveCounter = 0;
				const Location next = shnek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) ||
					shnek.IsInTileExceptEnd(next))
				{
					GameIsOver = true;
				}
				else
				{
					bool eating = next == apple.GetLocation();
                    bool eatingFake = next == FakeApple.GetLocation();
					if (eating)
					{
						shnek.Grow();
						shnekMovePeriod-=1;
					}
                    if (eatingFake)
				    {
						shnek.Grow();
						shnekMovePeriod += 1;
						++BouldersNow;
				    }
					shnek.MoveBy(delta_loc);
					if (eating)
					{
						apple.Respawn(rng, brd, shnek, FakeApple,boulders[100]);
					}
					if (eatingFake)
				    {
						FakeApple.Respawn(rng, brd, shnek, apple, boulders[100]);
					}
					for (int i = 0; i < BouldersNow; ++i)
					{
						
						bool Collided = next == boulders[i].GetLocation();
						if (Collided)
						{
							GameIsOver = true;
						}
					}

						
						
					
				}
			}
	}
	else
	{
		
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			GameIsStarted=true;
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			GameIsStarted = false;
			GameIsOver = false;
			BouldersNow = 0;
			apple.Respawn(rng, brd, shnek,FakeApple,boulders[50]);
			FakeApple.Respawn(rng, brd, shnek, apple,boulders[50]);
			shnekMovePeriod = 20;
			shnek = Snake({18,13});
		}
	}
}

void Game::ComposeFrame()
{
	if (GameIsStarted)
	{
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver(307, 158, gfx);
		}
		else
		{
			shnek.Draw(brd);
			apple.Draw(brd,Colors::Red);
			FakeApple.Draw(brd,Colors::MakeRGB(242,25,80 ));
			for (int i = 0; i < BouldersNow; ++i)
			{
				boulders[i].Draw(brd);
			}
			brd.DrawBorder();
		}
	}
	else
	{
		SpriteCodex::DrawTitleScreen(277, 132, gfx);
	}
}
