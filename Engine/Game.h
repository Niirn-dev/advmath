/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include "CoordinateTransformer.h"
#include "Camera.h"
#include "Entity.h"
#include <memory>
#include "FrameTimer.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	CoordinateTransformer ct;
	Camera cam;
	Vei2 prevMousePos = { 0,0 };
	static constexpr float worldWidth = 10000.0f;
	static constexpr float worldHeight = 6000.0f;
	static constexpr float minInnerRad = 40.0f;
	static constexpr float maxInnerRad = 200.0f;
	static constexpr float meanInnerRad = 120.0f;
	static constexpr float devInnerRad = 30.0f;
	static constexpr float minOuterRad = 220.0f;
	static constexpr float maxOuterRad = 600.0f;
	static constexpr float meanOuterRad = 340.0f;
	static constexpr float devOuterRad = 100.0;
	static constexpr int minFlares = 3;
	static constexpr int maxFlares = 20;
	static constexpr float minStarColorPhase = -3.14159f;
	static constexpr float maxStarColorPhase = 3.14159f;
	static constexpr float minStarColorFreq = 1.0f;
	static constexpr float maxStarColorFreq = 4.0f;
	static constexpr int nEntities = 120;
	std::vector<std::unique_ptr<Entity>> entityPtrs;
	/********************************/
};