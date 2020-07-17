#pragma once
#include <vector>
#include "Vec2.h"
#include "Drawable.h"


class Entity
{
public:
	Entity(std::vector<Vec2> model, const Vec2& pos = Vec2(0.0f, 0.0f), unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		: model(std::move(model)), pos(pos), r(r), g(g), b(b)
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
	Drawable GetDrawable() const
	{
		Drawable d(model, Colors::MakeRGB(r,g,b));
		d.Scale(scale);
		d.Translate(pos);
		return d;
	}
private:
	Vec2 pos = { 0.0f,0.0f };
	std::vector<Vec2> model;
protected:
	float scale = 1.0f;
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
};

