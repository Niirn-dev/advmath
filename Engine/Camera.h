#pragma once

#include "CoordinateTransformer.h"
#include "Graphics.h"
#include "Vec2.h"
#include <vector>

class Camera
{
public:
	Camera( CoordinateTransformer& ct,Vec2 pos = { 0.0f,0.0f },float scale = 1.0f )
		:
		ct( ct ),
		pos( pos ),
		scale( scale )
	{
	}

	inline void AddPosition( Vec2 dpos )
	{
		pos += dpos;
	}
	inline void SetPosition( Vec2 newPos )
	{
		pos = newPos;
	}
	inline Vec2 GetPosition() const
	{
		return pos;
	}
	inline void SetScale( float s )
	{
		scale = s;
	}
	inline float GetScale() const
	{
		return scale;
	}

	void DrawPolyline( std::vector<Vec2> verts,Color c ) const
	{
		for ( auto& v : verts )
		{
			v -= pos;
			v *= scale;
		}
		ct.DrawPolyline( std::move( verts ),c );
	}

private:
	CoordinateTransformer& ct;
	Vec2 pos;
	float scale;
};
