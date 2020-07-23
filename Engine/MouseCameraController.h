#pragma once
#include "Camera.h"
#include "Mouse.h"

class MouseCameraController
{
public:
	MouseCameraController(Mouse& mouse, Keyboard& kbd, Camera& cam)
		:
		mouse(mouse),
		kbd(kbd),
		cam(cam)
	{}
	void Update(float dt)
	{
		if (kbd.KeyIsPressed('Q'))
		{
			cam.SetAngle(cam.GetAngle() + rotFactor * dt);
		}
		if (kbd.KeyIsPressed('E'))
		{
			cam.SetAngle(cam.GetAngle() - rotFactor * dt);
		}
		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read();
			switch (e.GetType())
			{
			case Mouse::Event::Type::LPress:
				engaged = true;
				lastPos = (Vec2)e.GetPos();
				break;
			case Mouse::Event::Type::LRelease:
				engaged = false;
				break;
			case Mouse::Event::Type::WheelUp:
				cam.SetScale(cam.GetScale() * zoomFactor);
				break;
			case Mouse::Event::Type::WheelDown:
				cam.SetScale(cam.GetScale() / zoomFactor);
				break;
			}
		}

		if (engaged)
		{
			const auto curPos = (Vec2)mouse.GetPos();
			auto delta = curPos - lastPos;
			delta.x = -delta.x; //Fixes the disconnect between screen coords and math coords
			delta.Rotate(-cam.GetAngle()); //Fixes mouse movement when rotated
			cam.MoveBy(delta / cam.GetScale());
			lastPos = curPos;
		}
	}
private:
	static constexpr float zoomFactor = 1.2f;
	static constexpr float rotFactor = 2.0f;
	bool engaged = false;
	Vec2 lastPos;
	Mouse& mouse;
	Keyboard& kbd;
	Camera& cam;
};