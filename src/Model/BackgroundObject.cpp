# pragma once
# include <Siv3D.hpp>

# include "./Model/BackgroundObject.hpp"

namespace BeamForEyes::Model
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

	Mesh BackgroundObject::GetBackObstacleMesh() const
	{
		return backObstacleMesh;
	}

	PhongMaterial BackgroundObject::GetbackObstacleMaterial() const
	{
		return backObstacleMaterial;
	}

	BackgroundObject::BackgroundObject()
	{
		// オブジェクトランダム生成
		positions.clear();
		for (int i=0; i<backObstacleNum; i++)
		{
			positions.push_back(Vec3{ Random(-16*25, 16*25), Random(-9*25, 9*25), Random(500, 750) });
		}

		// マテリアル設定
		backObstacleMaterial.ambientColor = ColorF{ 1.0 };
		backObstacleMaterial.diffuseColor = ColorF{ 0.0 };
		backObstacleMaterial.emissionColor = Linear::Palette::Ghostwhite;
	}

	BackgroundObject::~BackgroundObject()
	{

	}
}
