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
#include "Vec2.h"
#include "Star.h"
#include <random>
#include <algorithm>
#include <iterator>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct( gfx ),
	cam( ct )
{
	std::mt19937 rng( std::random_device{}() );
	std::uniform_real_distribution<float> posDist( -2000.0f,2000.0f );
	std::uniform_real_distribution<float> inRadDist( 40.0f,120.0f );
	std::uniform_real_distribution<float> outRadDist( 140.0f,300.0f );
	std::uniform_int_distribution<int> flaresDist( 3,16 );
	std::uniform_int_distribution<unsigned int> cDist( 0,255 );
	entityPtrs.reserve( nEntities );
	std::generate_n( std::back_inserter( entityPtrs ),nEntities,
					 [&]() 
					 {
						 float outRad = outRadDist( rng );
						 float inRad = inRadDist( rng );
						 Vec2 pos;
						 do
						 {
							 pos = Vec2{ posDist( rng ),posDist( rng ) };
						 } while (
							 std::find_if( entityPtrs.begin(),entityPtrs.end(),
										   [&]( const std::unique_ptr<Entity>& pe )
										   {
											   Star* ps = reinterpret_cast<Star*>( pe.get() );
											   return pos.DistToSq( ps->GetPosition() ) < 
												   outRad * outRad + 2 * outRad * ps->GetOuterRadius() + ps->GetOuterRadius() * ps->GetOuterRadius();
										   }
							) != entityPtrs.end() );

						 return std::make_unique<Star>(
								 outRad,inRad,flaresDist( rng ),
								 pos,
								 Color{ unsigned char( cDist( rng ) ),
										unsigned char( cDist( rng ) ),
										unsigned char( cDist( rng ) )
								 }
						 );
					 } );
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
	while ( !wnd.mouse.IsEmpty() )
	{
		const auto e = wnd.mouse.Read();
		if ( e.GetType() == Mouse::Event::Type::LPress )
		{
			prevMousePos = e.GetPos();
		}
		else if ( e.GetType() == Mouse::Event::Type::WheelUp )
		{
			cam.SetScale( cam.GetScale() * 1.05f );
		}
		else if ( e.GetType() == Mouse::Event::Type::WheelDown )
		{
			cam.SetScale( cam.GetScale() * 0.95f );
		}
	}
	if ( wnd.mouse.LeftIsPressed() )
	{
		const Vei2 curMousePos = wnd.mouse.GetPos();
		Vec2 deltaPos = Vec2( curMousePos - prevMousePos );
		deltaPos.x *= -1.0f;

		cam.MoveBy( deltaPos / cam.GetScale() );
		prevMousePos = curMousePos;
	}
}

void Game::ComposeFrame()
{
	for ( const auto& pe : entityPtrs )
	{
		cam.Draw( std::move( pe->GetDrawable() ) );
	}
}
