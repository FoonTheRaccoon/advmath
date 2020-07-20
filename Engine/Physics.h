#pragma once
#include "Vec2.h"
#include "Entity.h"

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
		std::vector<Vec2> static_tmp = static_ent.GetModelRef();
		std::vector<Vec2> dyn_tmp = dyn_ent.GetModelRef();

		for (auto i = static_tmp.begin(); i != std::prev(static_tmp.end()); i++)
		{
				if (DistancePntFromLine(*i, *std::next(i), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
				{
					PntToCollide = dyn_ent.GetPos();
					LinePnt_1_ToCollide = *i;
					LinePnt_2_ToCollide = *std::next(i);
					return true;
				}
		}
		if (DistancePntFromLine(static_tmp.back(), static_tmp.front(), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
		{
			PntToCollide = dyn_ent.GetPos();
			LinePnt_1_ToCollide = static_tmp.back();
			LinePnt_2_ToCollide = static_tmp.front();
			return true;
		}
		
		return false;
	}
	float DistancePntFromLine(const Vec2& p1, const Vec2& p2, const Vec2& pnt)
	{
		return abs((p2.y - p1.y) * pnt.x - (p2.x - p1.x) * pnt.y + p2.x * p1.y - p2.y * p1.x) / sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
	}
	void DoCollision(Entity& static_ent, Entity& dyn_ent)
	{
		dyn_ent.SetVelocity(Vec2(-2.0f, -2.0f));
	}
private:
	Vec2 PntToCollide = { 0.0f, 0.0f };

	Vec2 LinePnt_1_ToCollide = { 0.0f, 0.0f };

	Vec2 LinePnt_2_ToCollide = { 0.0f, 0.0f };

	float collisionBufferDistance = 20.0f;
};