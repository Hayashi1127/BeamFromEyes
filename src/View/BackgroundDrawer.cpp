# pragma once

# include <Siv3D.hpp>

# include "./View/BackgroundDrawer.hpp"

using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	ColorF BackgroundDrawer::GetBackgroundColor() const
	{
		return backgroundObjectPtr->GetBackgroundColor();
	}

	BackgroundDrawer::BackgroundDrawer(const BackgroundObject* ptr)
	{
		backgroundObjectPtr = ptr;
	}

	void BackgroundDrawer::Draw()
	{
		Mesh meshes{ backgroundObjectPtr->GetBackObstacleMesh() };
		Array<Vec3> positions{ backgroundObjectPtr->GetBackObstaclePositions() };
		Quaternion rotation{ backgroundObjectPtr->GetBackObstacleRotation() };
		PhongMaterial material{ backgroundObjectPtr->GetbackObstacleMaterial() };
		for (int i = 0; i < backgroundObjectPtr->GetBackObstacleNum(); i++)
		{
			meshes.draw(positions.at(i), rotation, material);
		}
	}
}
