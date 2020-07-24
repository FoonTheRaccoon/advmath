#pragma once
#include <vector>
#include "Vec2.h"
#include "Drawable.h"


class Entity
{
public:
	Entity(std::vector<Vec2> model, const Vec2& pos = Vec2(0.0f, 0.0f), const Vec2& vel = Vec2(0.0f, 0.0f), float radius = 1.0f, unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		: model(std::move(model)), pos(pos), vel(vel), radius(radius), r(r), g(g), b(b)
	{}
	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos(const Vec2& newPos)
	{
		pos = newPos;
	}
	void TranslateBy(const Vec2& offset)
	{
		pos += offset;
	}
	void SetScale(const float& newScale)
	{
		scale = newScale;
	}
	float GetScale()
	{
		return scale;
	}
	void SetAngle(const float& newAngle)
	{
		angle = newAngle;
	}
	float GetAngle()
	{
		return angle;
	}
	const Vec2& GetVelocity() const
	{
		return vel;
	}
	void SetVelocity(const Vec2& vel_in)
	{
		vel = vel_in;
	}
	void UpdatePos()
	{
		pos += vel;
	}
	float GetMaxPntFromCenter_Radius() const
	{
		return radius;
	}
	bool IsCollidable() const
	{
		return collidable;
	}
	void CollidableSwitch()
	{
		if (collidable)
		{
			collidable = false;
		}
		else
		{
			collidable = true;
		}
	}
	Drawable GetDrawable() const
	{
		Drawable d(model, Colors::MakeRGB(r,g,b));
		d.ApplyTransformation(
			Mat3::Translation(pos.x, pos.y) *
			Mat3::Scale(scale) *
			Mat3::Rotate(angle)
			);
		return d;
	}
	std::vector<Vec2>& GetModelRef()
	{
		return model;
	}
private:
	Vec2 pos = { 0.0f,0.0f };
	Vec2 vel = { 0.0f, 0.0f };
	std::vector<Vec2> model;
	float scale = 1.0f;
	float angle = 0.0f;
	float radius = 1.0f;
	bool collidable = true;
public:
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
};

