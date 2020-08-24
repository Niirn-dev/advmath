#pragma once

#include "CoordinateTransformer.h"
#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "Drawable.h"

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

	inline void MoveBy( Vec2 offset )
	{
		pos += offset;
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

	void Draw( Drawable d ) const
	{
		d.Translate( -pos );
		d.Scale( scale );
		ct.Draw( std::move( d ) );
	}

private:
	CoordinateTransformer& ct;
	Vec2 pos;
	float scale;
};
