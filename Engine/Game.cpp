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


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct),
	cnt(wnd.mouse, cam),
	bounds(Star::Make(400.0f, 400.0f, 30), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 255, 0, 0, 400.0f),
	lilBounds(Star::Make(100.0f, 100.0f, 10), Vec2(100.0f, 100.0f), Vec2(0.0f, 0.0f), 0, 255, 0, 100.0f)
{
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(100.0f, 100.0f), Vec2(5.1f, -3.8f), 0, 100, 255, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(-300.0f, 0.0f), Vec2(10.1f, -0.8f), 100, 100, 25, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(0.0f, 0.0f), Vec2(-5.1f, 1.8f), 90, 100, 25, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(0.0f, -300.0f), Vec2(0.1f, -10.8f), 7, 10, 255, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(0.0f, 200.0f), Vec2(10.1f, 1.8f), 38, 100, 25, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(300.0f, 10.0f), Vec2(5.1f, -7.8f), 59, 10, 255, 20.0f);
	bouncers.emplace_back(Star::Make(20.0f, 20.0f, 10), Vec2(-10.0f, -100.0f), Vec2(-2.1f, -.8f), 78, 10, 255, 20.0f);
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
	float dt = ft.Mark();

	static Vec2 dir;
	const float speed = 2.0f;

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir = { 0.0f, speed };
		lilBounds.TranslateBy(dir);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir = { 0.0f, -speed };
		lilBounds.TranslateBy(dir);
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir = { -speed, 0.0f};
		lilBounds.TranslateBy(dir);
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir = { speed, 0.0f };
		lilBounds.TranslateBy(dir);
	}

	

	cnt.Update();
	for (auto& ent : bouncers)
	{
		ent.UpdatePos();
	}
	
	for (auto& ent : bouncers)
	{
		phy.Update(bounds, ent);
	}
	for (auto& ent : bouncers)
	{
		phy.Update(lilBounds, ent);
	}
}

void Game::ComposeFrame()
{
	//for(const auto& ent : stars)
	//	if (ent.GetPos().DistFromOtherVec2(cam.GetPos()) < gfx.ScreenLengthFromCenter / cam.GetScale() + ent.GetRadius())
	//		cam.Draw( ent.GetDrawable());

	cam.Draw(bounds.GetDrawable());
	cam.Draw(lilBounds.GetDrawable());
	for (auto& ent : bouncers)
	{
		cam.Draw(ent.GetDrawable());
	}
}

//Random StarField Generation
//Game::Game(MainWindow& wnd)
//	:
//	wnd(wnd),
//	gfx(wnd),
//	ct(gfx),
//	cam(ct),
//	cnt(wnd.mouse, cam),
//	rng(rd()),
//	xDist(-dist, dist),
//	yDist(-dist, dist),
//	inRadius(0.2f, 0.6f),
//	outRadius(50.0f, maxRad),
//	points(2, 8),
//	rgb(0, 255),
//	strobeSpeed(1.0f, 10.0f),
//	scaleFactor(0.05f, 0.95f)
//{
//	stars.reserve(entNum);
//	for (int i = 0; i < entNum; ++i)
//	{
//		float xDist_tmp = 0.0f;
//		float yDist_tmp = 0.0f;
//		float inRadius_tmp = inRadius(rng);
//		float outRadius_tmp = 0.0f;
//		int points_tmp = points(rng);
//		unsigned int r = rgb(rng);
//		unsigned int g = rgb(rng);
//		unsigned int b = rgb(rng);
//		float strobeSpeed_tmp = strobeSpeed(rng);
//		float scaleFactor_tmp = scaleFactor(rng);
//		bool placeable = true;
//
//		do
//		{
//			placeable = true;
//			xDist_tmp = xDist(rng);
//			yDist_tmp = yDist(rng);
//			outRadius_tmp = outRadius(rng);
//			for (const auto& ent : stars)
//			{
//				float xdiff = ent.GetPos().x - xDist_tmp;
//				float ydiff = ent.GetPos().y - yDist_tmp;
//				float distance = sqrt(xdiff * xdiff + ydiff * ydiff);
//				if (distance < (ent.GetRadius() + outRadius_tmp))
//				{
//					placeable = false;
//				}
//			}
//		} while (!placeable);
//		stars.emplace_back(Star::Make(inRadius_tmp * outRadius_tmp, outRadius_tmp, points_tmp), Vec2(xDist_tmp, yDist_tmp), r, g, b, outRadius_tmp, strobeSpeed_tmp, scaleFactor_tmp);
//	}
//
//}