#pragma once

#include "Vec2.h"
#include <vector>
#include "Graphics.h"
#include "Drawable.h"

class Entity
{
protected:
	Entity( std::vector<Vec2> model,Vec2 pos,Color c )
		:
		c ( c ),
		model( std::move( model ) ),
		pos( pos )
	{
	}
public:
	virtual ~Entity() = default;
	inline void TranslateBy( Vec2 offset )
	{
		pos += offset;
	}
	inline void SetPosition( Vec2 newPos )
	{
		pos = newPos;
	}
	inline const Vec2& GetPosition() const
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
	virtual float GetSize() const = 0;
	Drawable GetDrawable() const
	{
		Drawable drawable( model,c );
		drawable.Scale( scale );
		drawable.Translate( pos );
		return std::move( drawable );
	}
	inline Color GetColor() const
	{
		return c;
	}

private:
	Color c;
	std::vector<Vec2> model;
	Vec2 pos = { 0.0f,0.0f };
	float scale = 1.0f;
};
