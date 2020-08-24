#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx( gfx )
	{
	}

	void Draw( Drawable drawable ) const
	{
		const Vec2 offset = Vec2{ float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight / 2 ) };
		drawable.ScaleIndividually( 1.0f,-1.0f );
		drawable.Translate( offset );
		drawable.Render( gfx );
	}

private:
	Graphics& gfx;
};
