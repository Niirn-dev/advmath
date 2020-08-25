#pragma once

#include <vector>
#include "Vec2.h"
#include "Entity.h"

class Star : public Entity
{
public:
	Star( float outerRadius,float innerRadius,int nFlares,Vec2 pos,Color c )
		:
		Entity( Make( outerRadius,innerRadius,nFlares ),pos,c ),
		outRad( outerRadius ),
		inRad( innerRadius )
	{
	}
	inline float GetSize() const
	{
		return outRad;
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
};
