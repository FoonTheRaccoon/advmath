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
		for (auto i = static_ent.GetModelRef().begin(); i != std::prev(static_ent.GetModelRef().end()); i++)
		{
				if (DistancePntFromLine(*i, *std::next(i), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
				{
					CollidableWall = std::pair<Vec2, Vec2> (*i, *std::next(i));
					return true;
				}
		}
		if (DistancePntFromLine(static_ent.GetModelRef().back(), static_ent.GetModelRef().front(), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
		{
			CollidableWall = std::pair<Vec2, Vec2>(static_ent.GetModelRef().back(), static_ent.GetModelRef().front());
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

		
		Vec2 w = (CollidableWall.first - CollidableWall.second);
		w = w.GetNormalized();
		Vec2 v = dyn_ent.GetVelocity();
		dyn_ent.SetVelocity(w * (v * w) * 2.0f - v);


		float DistToClosestWall =  DistancePntFromLine(CollidableWall.first, CollidableWall.second, dyn_ent.GetPos());

		if (DistToClosestWall < dyn_ent.GetMaxPntFromCenter_Radius())
		{
			Vec2 Direction = (CollidableWall.first - CollidableWall.second).GetNormalized();
			Direction.MakeInverseVec();

			dyn_ent.SetPos(dyn_ent.GetPos() + (-Direction * (dyn_ent.GetMaxPntFromCenter_Radius() - DistToClosestWall)));
		}
	}
private:
	std::pair<Vec2,Vec2> CollidableWall;

	float collisionBufferDistance = 20.0f;
};