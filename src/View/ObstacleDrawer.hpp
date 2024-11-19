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
		ObstacleDrawer(const Array<Obstacle>* ptr, const ModelDatabase* ptr2);
		~ObstacleDrawer();
		void Draw();
	};
}
