# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Model
{
	class ModelDatabase
	{
	private:
	public:
		/// @brief 背景オブジェクトのメッシュ
		const Mesh backObstacleModel{ MeshData::TwoSidedPlane(1) };

		/// @brief 背景オブジェクトのマテリアル
		PhongMaterial backObstacleMaterial;

		/// @brief 障害物のモデルデータ
		const s3d::Model obstacleModel{ U"../ThirdParty/Quaternius_UltimateSpaceKit/Environment/OBJ/Planet_5.obj" };

		ModelDatabase();
		~ModelDatabase();
	};
}
