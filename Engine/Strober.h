#pragma once
#include <limits>
#include "Graphics.h"


class Strober
{
public:
	Strober(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0 , float rad = 0.0f, float strobeSpeed = 1.0f, float scaleFactor = 1.0f)
		: r(r), g(g), b(b),
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
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
	static constexpr float maxTime = std::numeric_limits<float>::max();
	float time = 0.0f;
	float initRadius = 0.0f;
	float curRadius = 0.0f;
	float strobeSpeed = 1.0f;
	float scaleFactor = 1.0f;
};