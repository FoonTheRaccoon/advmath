#pragma once
#include <limits>
#include "Graphics.h"
#include "Entity.h"


class Strober
{
public:
	Strober(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, float strobeSpeed = 1.0f, float scaleFactor = 1.0f, float spinFactor = 0.0f)
		: init_r(r), init_g(g), init_b(b),
		strobeSpeed(strobeSpeed),
		scaleFactor(scaleFactor),
		spinFactor(spinFactor)
	{}
	void Strobe(float dt, Entity& entity)
	{
		time += dt;

		if (time >= maxTime)
			time = 0.0f;

		entity.r = int(100.0f * sin(time * strobeSpeed + init_r) + 140.0f);
		entity.g = int(100.0f * sin(time * strobeSpeed + init_g) + 140.0f);
		entity.b = int(100.0f * sin(time * strobeSpeed + init_b) + 140.0f);

		float scale_diff = 1.0f - scaleFactor;
		float scale_swing = scale_diff / 2.0f;

		float scale_tmp = scale_swing * sin(time * strobeSpeed) + (1.0f - scale_swing);
		entity.SetScale(scale_tmp);

		entity.SetAngle(entity.GetAngle() + spinFactor);
	}
private:
	static constexpr float maxTime = std::numeric_limits<float>::max();
	float time = 0.0f;
	float strobeSpeed = 1.0f;
	float scaleFactor = 1.0f;
	float spinFactor = 0.0f;
	unsigned int init_r = 0;
	unsigned int init_g = 0;
	unsigned int init_b = 0;
};