#pragma once
#include "Vec2.h"
#include "Entity.h"
#define PI 3.14159265359f

class Physics
{
public:
	void Update(Entity& static_ent, Entity& dyn_ent)
	{
		if (dyn_ent.IsCollidable())
		{
			if (AreCloseEnoughToCheck(static_ent, dyn_ent))
			{
				if (DoVertsOverlap(static_ent, dyn_ent))
				{
					DoCollision(static_ent, dyn_ent);
				}
			}
		}
	}
private:
	bool AreCloseEnoughToCheck(Entity& static_ent, Entity& dyn_ent)
	{
		return static_ent.GetPos().DistFromOtherVec2(dyn_ent.GetPos()) < (static_ent.GetMaxPntFromCenter_Radius() + dyn_ent.GetMaxPntFromCenter_Radius());
	}
	bool DoVertsOverlap(Entity& static_ent, Entity& dyn_ent)
	{
		bool isOverlapping = false;

		static std::vector<std::pair<Vec2, Vec2>> CollidableWalls;
		CollidableWalls.reserve(10);

		static Vec2 p1;
		static Vec2 p2;

		for (auto i = static_ent.GetModelRef().begin(); i != std::prev(static_ent.GetModelRef().end()); i++)
		{
			p1 = *i;
			p2 = *std::next(i);

			TransformPoints(p1, p2, static_ent);
			
			if (ObjCanCollideWithLineSegment(p1, p2, static_ent, dyn_ent))
			{
				
				CollidableWalls.emplace_back(std::pair<Vec2, Vec2> (p1, p2));
				isOverlapping = true;
			}
		}

		p1 = static_ent.GetModelRef().back();
		p2 = static_ent.GetModelRef().front();

		TransformPoints(p1, p2, static_ent);

		if (ObjCanCollideWithLineSegment(p1, p2, static_ent, dyn_ent))
		{
			CollidableWalls.emplace_back(std::pair<Vec2, Vec2>(p1, p2));
			isOverlapping = true;
		}
		
		//Closest to midpoint
		if (isOverlapping)
		{
			std::sort(CollidableWalls.begin(), CollidableWalls.end(),
				[&](std::pair<Vec2, Vec2> wall1, std::pair<Vec2, Vec2> wall2)
				{
					return MidPointOfLineSegment(wall1.first, wall1.second).DistFromOtherVec2(dyn_ent.GetPos()) 
						< MidPointOfLineSegment(wall2.first, wall2.second).DistFromOtherVec2(dyn_ent.GetPos());
				});
			CollidableWall = CollidableWalls[0];
		}
		
		CollidableWalls.clear();
		return isOverlapping;
	}
	float DistancePntFromLine(const Vec2& p1, const Vec2& p2, const Vec2& pnt)
	{
		return abs((p2.y - p1.y) * pnt.x - (p2.x - p1.x) * pnt.y + p2.x * p1.y - p2.y * p1.x) / sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
	}
	bool ObjCanCollideWithLineSegment(const Vec2& p1, const Vec2& p2, Entity& static_ent, Entity& dyn_ent)
	{
		if (DistancePntFromLine(p1, p2, dyn_ent.GetPos()) > dyn_ent.GetMaxPntFromCenter_Radius())
		{
			return false;
		}

		static Vec2 v, l;
		static float v_mag, l_mag, theta;

		v = dyn_ent.GetVelocity();
		v_mag = v.Len();

		l = GetLineNorm(p1, p2, static_ent, dyn_ent);
		l_mag = l.Len();

		theta = acos((v * l)/ (v_mag * l_mag));

		if (abs(theta) < (PI / 2))
		{
			return false;
		}
		
		return true;
	}
	Vec2& GetLineNorm(const Vec2& p1, const Vec2& p2, Entity& static_ent, Entity& dyn_ent)
	{
		static Vec2 LineNorm;
		LineNorm = MidPointOfLineSegment(p1, p2) - static_ent.GetPos();

		if (static_ent.GetPos().DistFromOtherVec2(dyn_ent.GetPos()) < static_ent.GetMaxPntFromCenter_Radius())
		{
			LineNorm = -LineNorm;
		}

		return LineNorm;
	}
	Vec2& MidPointOfLineSegment(const Vec2& p1, const Vec2& p2)
	{
		static Vec2 MidPnt;
		static float dy, mid_y, dx, mid_x;

		dy = p1.y - p2.y;
		mid_y = p1.y + (dy / 2.0f);

		dx = p1.x - p2.x;
		mid_x = p1.x + (dx / 2.0f);

		MidPnt = { mid_x , mid_y };

		return MidPnt;
	}
	void TransformPoints(Vec2& p1, Vec2& p2, Entity& static_ent)
	{

		const float COS = cos(static_ent.GetAngle());
		const float SIN = sin(static_ent.GetAngle());
		
		p1.Rotate(COS, SIN);
		p1 *= static_ent.GetScale();
		p1 += static_ent.GetPos();

		p2.Rotate(COS, SIN);
		p2 *= static_ent.GetScale();
		p2 += static_ent.GetPos();
	}
	void DoCollision(Entity& static_ent, Entity& dyn_ent)
	{
		Vec2 init_vel = dyn_ent.GetVelocity();
		
		Vec2 w = (CollidableWall.first - CollidableWall.second);
		w = w.GetNormalized();
		Vec2 v = init_vel;
		dyn_ent.SetVelocity((w * (v * w) * 2.0f - v) * reboudEff);

		float DistToClosestWall = DistancePntFromLine(CollidableWall.first, CollidableWall.second, dyn_ent.GetPos());
		
		if (DistToClosestWall < dyn_ent.GetMaxPntFromCenter_Radius())
		{
			Vec2 Direction = init_vel.GetNormalized();
		
			Direction = Direction * -1.0f;
		
			dyn_ent.SetPos(dyn_ent.GetPos() + (Direction * (dyn_ent.GetMaxPntFromCenter_Radius() - DistToClosestWall + 1.0f)));
		}

	}
private:
	std::pair<Vec2,Vec2> CollidableWall;
	float reboudEff = 1.0f;
};