#pragma once

#include "CoordinateTransformer.h"
#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "Drawable.h"
#include "Star.h"

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

	void Draw( Drawable drawable ) const
	{
		drawable.Translate( -pos );
		drawable.Scale( scale );
		ct.Draw( std::move( drawable ) );
	}
	bool ContainsCircle( const Vec2& center,float radius ) const
	{
		auto screenRect = ct.GetScreenRect();
		screenRect.Scale( 1.0f / scale );
		screenRect.Translate( pos );
		Vec2 testPoint = center;

		if ( testPoint.x < screenRect.left )
			testPoint.x = screenRect.left;
		else if ( testPoint.x > screenRect.right )
			testPoint.x = screenRect.right;
		if ( testPoint.y < screenRect.bottom )
			testPoint.y = screenRect.bottom;
		else if ( testPoint.y > screenRect.top )
			testPoint.y = screenRect.top;

		return ( testPoint.DistToSq( center ) <= radius * radius );
	}

private:
	CoordinateTransformer& ct;
	Vec2 pos;
	float scale;
};
