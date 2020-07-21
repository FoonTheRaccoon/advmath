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
		bool isOverlapping = false;

		static std::vector<std::pair<Vec2, Vec2>> CollidableWalls;
		CollidableWalls.reserve(10);

		for (auto i = static_ent.GetModelRef().begin(); i != std::prev(static_ent.GetModelRef().end()); i++)
		{
				if (DistancePntFromLine(*i, *std::next(i), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
				{
					CollidableWalls.emplace_back(std::pair<Vec2, Vec2> (*i, *std::next(i)));
					isOverlapping = true;
				}
		}
		if (DistancePntFromLine(static_ent.GetModelRef().back(), static_ent.GetModelRef().front(), dyn_ent.GetPos()) <= dyn_ent.GetMaxPntFromCenter_Radius())
		{
			CollidableWalls.emplace_back(std::pair<Vec2, Vec2>(static_ent.GetModelRef().back(), static_ent.GetModelRef().front()));
			isOverlapping = true;
		}
		
		if (isOverlapping)
		{
			std::sort(CollidableWalls.begin(), CollidableWalls.end(), 
				[&](std::pair<Vec2, Vec2> wall1, std::pair<Vec2, Vec2> wall2)
					{
					return DistancePntFromLine(wall1.first, wall1.second, dyn_ent.GetPos()) < DistancePntFromLine(wall2.first, wall2.second, dyn_ent.GetPos());
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
	void DoCollision(Entity& static_ent, Entity& dyn_ent)
	{
		Vec2 init_vel = dyn_ent.GetVelocity();
		
		Vec2 w = (CollidableWall.first - CollidableWall.second);
		w = w.GetNormalized();
		Vec2 v = init_vel;
		dyn_ent.SetVelocity((w * (v * w) * 2.0f - v) * reboudEff);


		float DistToClosestWall =  DistancePntFromLine(CollidableWall.first, CollidableWall.second, dyn_ent.GetPos());

		if (DistToClosestWall < dyn_ent.GetMaxPntFromCenter_Radius())
		{
			Vec2 Direction = init_vel.GetNormalized();

			Direction = Direction * -1.0f;

			dyn_ent.SetPos(dyn_ent.GetPos() + (Direction * (dyn_ent.GetMaxPntFromCenter_Radius() - DistToClosestWall)));
		}

	}
private:
	std::pair<Vec2,Vec2> CollidableWall;

	float reboudEff = 1.0f;
};