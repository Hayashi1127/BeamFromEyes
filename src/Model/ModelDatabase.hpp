# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Model
{
	class ModelDatabase
	{
	public:
		static const s3d::Model obstacleModel;

		ModelDatabase();
		~ModelDatabase();
	};
}
