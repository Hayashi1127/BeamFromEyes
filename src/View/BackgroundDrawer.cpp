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

	BackgroundDrawer::BackgroundDrawer(const BackgroundObject* ptr, const ModelDatabase* ptr2)
	{
		backgroundObjectPtr = ptr;
		modelDatabasePtr = ptr2;
	}

	void BackgroundDrawer::Draw()
	{
		Array<Vec3> positions{ backgroundObjectPtr->GetBackObstaclePositions() };
		Quaternion rotation{ backgroundObjectPtr->GetBackObstacleRotation() };
		for (int i = 0; i < backgroundObjectPtr->GetBackObstacleNum(); i++)
		{
			modelDatabasePtr->backObstacleModel.draw(positions.at(i), rotation, modelDatabasePtr->backObstacleMaterial);
		}
	}
}
