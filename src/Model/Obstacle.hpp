# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Model
{
	class Obstacle
	{
	private:
		/// @brief 障害物のヒットポイント
		int32 hp{ 100 };

		/// @brief 障害物の攻撃力
		int32 atp{ 10 };

		/// @brief 障害物の位置
		Vec3 position;
	public:
		Obstacle(const Vec3 position);
		~Obstacle();

		/// @brief ダメージを受ける
		void ReceiveDamage(const int32 enemyAtp);

		/// @brief ダメージを与える
		int32 Attack();
	};
}
