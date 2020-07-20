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
	bounds(Star::Make(400.0f, 400.0f, 8), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 255, 100, 0, 400.0f),
	bouncer(Star::Make(40.0f, 40.0f, 3), Vec2(0.0f, 0.0f), Vec2(1.1f, 0.8f), 0, 100, 255, 40.0f)
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
	float dt = ft.Mark();

	cnt.Update();
	bouncer.UpdatePos();
	
	phy.Update(bounds, bouncer);
}

void Game::ComposeFrame()
{
	//for(const auto& ent : stars)
	//	if (ent.GetPos().DistFromOtherVec2(cam.GetPos()) < gfx.ScreenLengthFromCenter / cam.GetScale() + ent.GetRadius())
	//		cam.Draw( ent.GetDrawable());

	cam.Draw(bounds.GetDrawable());
	cam.Draw(bouncer.GetDrawable());
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