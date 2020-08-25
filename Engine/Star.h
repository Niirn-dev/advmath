#pragma once

#include <vector>
#include "Vec2.h"
#include "Entity.h"
#include <algorithm>

class Star : public Entity
{
public:
	Star( float outerRadius,float innerRadius,int nFlares,Vec2 pos,Color c,float phase,float freq )
		:
		Entity( Make( outerRadius,innerRadius,nFlares ),pos,c ),
		outRad( outerRadius ),
		inRad( innerRadius ),
		baseColor( c ),
		colorPhase( phase ),
		colorFreq( freq )
	{
	}
	inline float GetSize() const override
	{
		return outRad;
	}
	void Update( float dt ) override
	{
		Color c;
		const int offset = int( 127.0f + 128.0f * sinf( colorFreq * time + colorPhase ) );
		c.SetR( std::min( 255,baseColor.GetR() + offset ) );
		c.SetG( std::min( 255,baseColor.GetG() + offset ) );
		c.SetB( std::min( 255,baseColor.GetB() + offset ) );

		time += dt;
		SetColor( c );

		const float scale_factor = sinf( 3.0f * colorFreq * time + colorPhase / 2.0f ) + 2.0f;
		SetScale( baseScale / scale_factor );
	}

private:
	std::vector<Vec2> Make( float outerRadius,float innerRadius,int nFlares = 5 )
	{
		std::vector<Vec2> star;
		star.reserve( 2 * size_t( nFlares ) );
		const float dTheta = 2.0f * 3.14159f / float( 2 * nFlares );
		for ( int i = 0; i < 2 * nFlares; ++i )
		{
			const float rad = ( i % 2 == 0 ) ? outerRadius : innerRadius;
			star.emplace_back(
				rad * cosf( dTheta * float( i ) ),
				rad * sinf( dTheta * float( i ) )
			);
		}
		return star;
	}

private:
	float outRad;
	float inRad;
	const Color baseColor;
	const float colorPhase;
	const float colorFreq;
	const float baseScale = 1.0f;
	float time = 0.0f;
};
