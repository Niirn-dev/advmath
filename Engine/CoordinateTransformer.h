#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx( gfx )
	{
	}

	void DrawPolyline( std::vector<Vec2> verts,Color c ) const
	{
		const Vec2 offset = Vec2{ float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight / 2 ) };
		for ( auto& v : verts )
		{
			v.y *= -1.0f;
			v += offset;
		}
		gfx.DrawPolyline( std::move( verts ),c );
	}

private:
	Graphics& gfx;
};
