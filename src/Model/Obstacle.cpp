# pragma once
# include <Siv3D.hpp>

# include "./Model/Obstacle.hpp"

namespace BeamFromEyes::Model
{
	Vec3 Obstacle::GetPosition() const
	{
		return position;
	}

	Quaternion Obstacle::GetRotation() const
	{
		return rotation;
	}

	bool Obstacle::IsReached()
	{
		return position.z < 0;
	}

	void Obstacle::ReceiveDamage(const int32 enemyAtp)
	{
		hp -= enemyAtp;
	}

	int32 Obstacle::Attack()
	{
		return atp;
	}

	void Obstacle::Update()
	{
		position -= moveSpeed;
		rotation *= Quaternion::RotationAxis(rotationAxis, rotationSpeed);
	}

	Obstacle::Obstacle()
	{
		position = Vec3{ Random(-xPosLim, xPosLim), Random(-yPosLim, yPosLim), zPosLim };

		moveSpeed = Vec3{ 0, 0, Random(0.5, 1.5) };
		rotationAxis = Vec3{ RandomVec2(), 0};
	}

	Obstacle::Obstacle(const Vec3 pos)
	{
		position = pos;
	}

	Obstacle::Obstacle(const Vec3 pos, const Quaternion rot)
	{
		position = pos;
		rotation = rot;
	}

	Obstacle::~Obstacle()
	{

	}
}
