#pragma once
#include <limits>
#include "Graphics.h"
#include "Entity.h"


class Strober
{
public:
	Strober(float rad = 0.0f, float strobeSpeed = 1.0f, float scaleFactor = 1.0f)
		: 
		initRadius(rad), curRadius(rad),
		strobeSpeed(strobeSpeed),
		scaleFactor(scaleFactor)
	{}
	void Strobe(float dt)
	{
		time += dt;

		if (time >= maxTime)
			time = 0.0f;
	}
private:
	static constexpr float maxTime = std::numeric_limits<float>::max();
	float time = 0.0f;
	float initRadius = 0.0f;
	float curRadius = 0.0f;
	float strobeSpeed = 1.0f;
	float scaleFactor = 1.0f;
};