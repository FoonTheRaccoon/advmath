#pragma once
#include <vector>
#include "Vec2.h"
#include "Entity.h"
#include "Strober.h"



class Star : public Entity
{
public:
	Star(std::vector<Vec2> model, const Vec2& pos = Vec2(0.0f, 0.0f), const Vec2& vel = Vec2(0.0f, 0.0f), unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, float rad = 1.0f, float strobeSpeed = 1.0f, float scaleFactor = 1.0f)
		: Entity(model, pos, vel, rad, r, g, b), strobie(r, g, b, strobeSpeed, scaleFactor)
	{}
	static std::vector<Vec2> Make( float outerRadius,float innerRadius,int nFlares = 5 )
	{
		std::vector<Vec2> star;
		star.reserve((__int64)nFlares * 2 );
		const float dTheta = 2.0f * 3.14159f / float( nFlares * 2 );
		for( int i = 0; i < nFlares * 2; i++ )
		{
			const float rad = (i % 2 == 0) ? outerRadius : innerRadius;
			star.emplace_back(
				rad * cos(float( i ) * dTheta ),
				rad * sin(float( i ) * dTheta )
			);
		}
		return star;
	}
	void Strobe(float dt)
	{
		strobie.Strobe(dt, *this);
	}
private:
	Strober strobie;
};