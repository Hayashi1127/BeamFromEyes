# pragma once
# include <Siv3D.hpp>

# include "./Model/CircleProgressBar.hpp"

namespace BeamFromEyes::Model
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

		/// @brief 上部UI画面
		const s3d::Texture texUpperUI{ U"../img/UpperUI.png" };

		/// @brief 下部UI画面
		const s3d::Texture texUnderUI{ U"../img/UnderUI.png" };

		mutable CircleProgressBar moistureBar{ Circle(0, 0, 40), 300};

		ModelDatabase();
		~ModelDatabase();
	};
}
