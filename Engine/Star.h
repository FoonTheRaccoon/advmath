#pragma once
#include <vector>
#include "Vec2.h"
#include "Entity.h"



class Star : public Entity
{
public:
	Star(std::vector<Vec2> model, const Vec2& pos = Vec2(0.0f, 0.0f), unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, float rad = 0.0f, float strobeSpeed = 1.0f, float scaleFactor = 1.0f)
		: Entity(model, pos, r, g, b), radius( rad )
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
	void Update(float dt)
	{
		strobie.Strobe(dt);
	}
	float GetRadius() const
	{
		return radius;
	}
private:
	float radius = 0.0f;
};