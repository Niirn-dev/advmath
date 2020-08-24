#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>

class Drawable
{
public:
	Drawable( std::vector<Vec2> model,Color c )
		:
		c( c ),
		model( std::move( model ) )
	{
	}

	void Translate( const Vec2& offset )
	{
		translation += offset;
	}
	void Scale( float factor )
	{
		scale_x *= factor;
		scale_y *= factor;
		translation *= factor;
	}
	void ScaleIndividually( float factor_x,float factor_y )
	{
		scale_x *= factor_x;
		scale_y *= factor_y;
		translation.x *= factor_x;
		translation.y *= factor_y;
	}
	std::vector<Vec2> GetPolyline() const
	{
		auto verts = model;
		for ( auto& v : verts )
		{
			v.x *= scale_x;
			v.y *= scale_y;
			v += translation;
		}
		return std::move( verts );
	}
	inline Color GetColor() const
	{
		return c;
	}

private:
	Color c;
	std::vector<Vec2> model;
	Vec2 translation = { 0.0f,0.0f };
	float scale_x = 1.0f;
	float scale_y = 1.0f;
};
