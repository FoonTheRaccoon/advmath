#pragma once
#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera(CoordinateTransformer& ct)
		: ct(ct)
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy(const Vec2& offset)
	{
		pos += offset;
	}
	void MoveTo(const Vec2& newPos)
	{
		pos = newPos;
	}
	float GetScale()
	{
		return scale;
	}
	void SetScale(const float& s)
	{
		scale = s;
	}
	void SetAngle(const float& newAngle)
	{
		angle = newAngle;
	}
	float GetAngle()
	{
		return angle;
	}
	void Draw(Drawable& drawable) const
	{
		drawable.ApplyTransformation(
			Mat3::Rotate(angle) *
			Mat3::Scale(scale) *
			Mat3::Translation(-pos.x, -pos.y)
		);
		ct.Draw(drawable);
	}
private:
	float scale = 1.0f;
	float angle = 0.0f;
	Vec2 pos = { 0.0f,0.0f };
	CoordinateTransformer& ct;

};