# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Model
{
	class ModelDatabase
	{
	private:
	public:
		const Mesh backObstacleModel{ MeshData::TwoSidedPlane(1) };
		const s3d::Model obstacleModel{ U"../ThirdParty/Quaternius_UltimateSpaceKit/Environment/OBJ/Planet_5.obj" };

		PhongMaterial backObstacleMaterial;

		ModelDatabase();
		~ModelDatabase();
	};
}
