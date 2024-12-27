# pragma once

# include <Siv3D.hpp>

# include "./View/BackgroundDrawer.hpp"

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	ColorF BackgroundDrawer::GetBackgroundColor() const
	{
		return backgroundObjectPtr->GetBackgroundColor();
	}

	BackgroundDrawer::BackgroundDrawer(const BackgroundObject* objPtr, const ModelDatabase* databasePtr)
	{
		backgroundObjectPtr = objPtr;
		modelDatabasePtr = databasePtr;
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
