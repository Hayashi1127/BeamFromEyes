# pragma once
# include <Siv3D.hpp>

# include "./Model/BackgroundObject.hpp"

namespace BeamFromEyes::Model
{
	ColorF BackgroundObject::GetBackgroundColor() const
	{
		return backgroundColor;
	}

	void BackgroundObject::SetBackgroundColor(ColorF color)
	{
		backgroundColor = color;
	}

	int32 BackgroundObject::GetBackObstacleNum() const
	{
		return backObstacleNum;
	}

	Array<Vec3> BackgroundObject::GetBackObstaclePositions() const
	{
		return positions;
	}

	void BackgroundObject::SetBackObstaclePositions(Array<Vec3> positions)
	{
		this->positions = positions;
	}

	Quaternion BackgroundObject::GetBackObstacleRotation() const
	{
		return rotation;
	}

	BackgroundObject::BackgroundObject()
	{
		// オブジェクトランダム生成
		positions.clear();
		for (int i=0; i<backObstacleNum; i++)
		{
			positions.push_back(Vec3{ Random(-16*25, 16*25), Random(-9*25, 9*25), Random(500, 750) });
		}
	}

	BackgroundObject::~BackgroundObject()
	{

	}
}
