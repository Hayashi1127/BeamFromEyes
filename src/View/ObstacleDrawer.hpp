# pragma once

# include <Siv3D.hpp>

# include <Model.hpp>

# include "./Model/Obstacle.hpp"

using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	class ObstacleDrawer
	{
	private:
		const Array<Obstacle>* obstaclePtr;
		const ModelDatabase* modelDatabasePtr;

	public:
		ObstacleDrawer(const Array<Obstacle>* objPtr, const ModelDatabase* databasePtr);
		~ObstacleDrawer();
		void Draw();
	};
}
