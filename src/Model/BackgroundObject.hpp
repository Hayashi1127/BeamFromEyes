# pragma once

# include <Siv3D.hpp>

namespace BeamFromEyes::Model
{
	class BackgroundObject
	{
	private:
		/// @brief 背景オブジェクトの数
		const int32 backObstacleNum{ 100 };

		/// @brief 背景オブジェクトの場所の配列、要素数はbackObstacleNum
		Array<Vec3> positions;

		/// @brief 背景オブジェクトの回転の配列、要素数はbackObstacleNum
		const Quaternion rotation{ Quaternion::RotateX(-90_deg) * Quaternion::RotateZ(45_deg) };

		/// @brief 背景の色
		ColorF backgroundColor{ Palette::Black };

	public:
		BackgroundObject();
		~BackgroundObject();

		/// @brief 背景の色を取得
		ColorF GetBackgroundColor() const;

		/// @brief 背景の色を設定する
		void SetBackgroundColor(ColorF color);

		/// @brief 背景オブジェクトの数を取得
		int32 GetBackObstacleNum() const;

		/// @brief 背景オブジェクトの位置を取得
		Array<Vec3> GetBackObstaclePositions()const;

		void SetBackObstaclePositions(Array<Vec3> positions);

		/// @brief 背景オブジェクトの回転を取得
		Quaternion GetBackObstacleRotation() const;
	};
}
