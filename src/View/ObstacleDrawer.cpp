# pragma once

# include <Siv3D.hpp>

# include <Model.hpp>

# include "./Model/Obstacle.hpp"
# include "./View/ObstacleDrawer.hpp"

using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	void ObstacleDrawer::Draw()
	{
		for (int i = 0; i < obstaclePtr->size(); i++)
		{
			modelDatabasePtr->obstacleModel.draw(obstaclePtr->at(i).GetPosition(), obstaclePtr->at(i).GetRotation());
		}
	}

	ObstacleDrawer::ObstacleDrawer(const Array<Obstacle>* objPtr, const ModelDatabase* databasePtr)
	{
		obstaclePtr = objPtr;
		modelDatabasePtr = databasePtr;
	}

	ObstacleDrawer::~ObstacleDrawer()
	{

	}
}
