#pragma once

#include "Graphics.h"
#include "Rect.h"
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
	template<typename T>
	static _Vec2<T> TransformVec2( _Vec2<T> v )
	{
		const _Vec2<T> offset = _Vec2<T>{ T( Graphics::ScreenWidth / 2 ),T( Graphics::ScreenHeight / 2 ) };
		v.y *= T( -1 );
		v += offset;
		return v;
	}
	static RectF GetScreenRect()
	{
		const Vec2 offset = Vec2{ float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight / 2 ) };
		auto screenRect = RectF( -offset,offset );
		screenRect.Scale( 1.0f,-1.0f );
		return screenRect;
	}

private:
	Graphics& gfx;
};
