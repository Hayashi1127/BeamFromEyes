# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Model
{
	class ModelDatabase
	{
	public:
		static const Mesh backObstacleModel;
		static const s3d::Model obstacleModel;

		static PhongMaterial backObstacleMaterial;

		ModelDatabase();
		~ModelDatabase();
	};
}
