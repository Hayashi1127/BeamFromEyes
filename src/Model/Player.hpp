# pragma once
# include <Siv3D.hpp>

# include "./Controller/IPointerReceiver.hpp"

using namespace BeamFromEyes::Controller;

namespace BeamFromEyes::Model
{
	class Player
	{
	private:
		/// @brief プレイヤー（守るべき星）のヒットポイント
		int32 hp{ 50 };

		/// @brief プレイヤーの攻撃力
		int32 atp{ 10 };

		/// @brief カーソルの位置
		Vec3 position{ 0, 0, -10 };

		/// @brief 目の渇き度合
		int32 eyeMoisture{ 100 };

		const IPointerReceiver* pointerReceiverPtr;
	public:
		Player(const IPointerReceiver* pointerReceiverPtr);
		~Player();
		void Update();

		/// @brief ダメージを受ける
		void ReceiveDamage(const int32 enemyAtp);

		/// @brief ダメージを与える
		int32 BeamAttack();

		/// @brief 目が渇く
		/// @param moisture 渇き度合
		void DryMoisture(const int32 dry);

		/// @brief 目の潤いが回復する
		/// @return 回復する渇き度合
		void RecoveryMoisture(const int32 moisture);

		int32 GetHP() const;

		int32 GetMoisture() const;

		Vec3 GetPosition() const;
	};
}
