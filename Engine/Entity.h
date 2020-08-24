#pragma once

#include "Vec2.h"
#include <vector>
#include "Graphics.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model,Vec2 pos,Color c )
		:
		c ( c ),
		model( std::move( model ) ),
		pos( pos )
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
	std::vector<Vec2> GetModel() const
	{
		std::vector<Vec2> verts = model;
		for ( auto& v : verts )
		{
			v += pos;
		}
		return verts;
	}
	inline Color GetColor() const
	{
		return c;
	}

private:
	Color c;
	std::vector<Vec2> model;
	Vec2 pos;
};
