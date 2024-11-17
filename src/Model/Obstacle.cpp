# pragma once
# include <Siv3D.hpp>

# include "./Model/Obstacle.hpp"

namespace BeamForEyes::Model
{
	void Obstacle::ReceiveDamage(const int32 enemyAtp)
	{
		hp -= enemyAtp;
	}

	int32 Obstacle::Attack()
	{
		return atp;
	}

	Obstacle::Obstacle(const Vec3 position)
	{
		this->position = position;
	}

	Obstacle::~Obstacle()
	{

	}
}
