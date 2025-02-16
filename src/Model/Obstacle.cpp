# pragma once
# include <Siv3D.hpp>

# include "./Model/Obstacle.hpp"

namespace BeamFromEyes::Model
{
	int32 Obstacle::GetHP() const
	{
		return hp;
	}

	Vec3 Obstacle::GetPosition() const
	{
		return position;
	}

	Quaternion Obstacle::GetRotation() const
	{
		return rotation;
	}

	Sphere Obstacle::GetCollider() const
	{
		return collider;
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
		collider.setPos(position);
	}

	Obstacle::Obstacle()
	{
		position = Vec3{ Random(-xPosLim, xPosLim), Random(-yPosLim, yPosLim), zPosLim };
		moveSpeed = Vec3{ 0, 0, Random(2.0, 3.0) };
		rotationAxis = Vec3{ RandomVec2(), 0};
		collider = Sphere(position, colliderSize);
	}

	Obstacle::Obstacle(const Vec3 pos)
	{
		position = pos;
		moveSpeed = Vec3{ 0, 0, Random(2.0, 3.0) };
		collider = Sphere(position, colliderSize);
	}

	Obstacle::Obstacle(const Vec3 pos, const Quaternion rot)
	{
		position = pos;
		moveSpeed = Vec3{ 0, 0, Random(2.0, 3.0) };
		rotation = rot;
		collider = Sphere(position, colliderSize);
	}

	Obstacle::~Obstacle()
	{

	}
}
