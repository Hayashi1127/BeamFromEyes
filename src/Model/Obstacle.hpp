# pragma once

# include <Siv3D.hpp>

namespace BeamFromEyes::Model
{
	class Obstacle
	{
	private:
		/// @brief zが0の時にギリギリ見えるx座標は6.0、結構外側も許容する
		double xPosLim{ 16.0 };

		/// @brief zが0の時にギリギリ見えるy座標は3.0、結構外側も許容する
		double yPosLim{ 9.0 };

		/// @brief z座標の最大値
		double zPosLim{ 500.0 };

		/// @brief 障害物のヒットポイント
		int32 hp{ 100 };

		/// @brief 障害物の攻撃力
		int32 atp{ 10 };

		/// @brief 障害物の位置
		Vec3 position;

		/// @brief 障害物の移動の速さ、正確には更新のたびにpositionに加算する量
		Vec3 moveSpeed;

		/// @brief 障害物の回転
		Quaternion rotation;

		/// @brief 障害物の回転の速さ、正確には更新のたびにrotationに加算する量
		float rotationSpeed{ 0.01 };

		/// @brief 障害物の回転軸
		Vec3 rotationAxis;

		/// @brief 当たり判定用
		Sphere collider;

		/// @brief コライダーの大きさ
		double colliderSize{ 3.0 };
	public:
		Obstacle();
		Obstacle(Vec3 pos);
		Obstacle(Vec3 pos, Quaternion rot);
		~Obstacle();

		int32 GetHP() const;

		/// @brief 位置の取得 
		Vec3 GetPosition() const;

		/// @brief 回転の取得
		Quaternion GetRotation() const;

		Sphere GetCollider() const;

		/// @brief 障害物が攻撃判定範囲に到達しているか
		bool IsReached();

		/// @brief ダメージを受ける
		void ReceiveDamage(const int32 enemyAtp);

		/// @brief ダメージを与える
		int32 Attack();

		void Update();
	};
}
