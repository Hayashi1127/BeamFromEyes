#pragma once
# include <Siv3D.hpp>

#include "./Model/Player.hpp"

namespace BeamFromEyes::Model
{
	class UIState
	{
	private:
		const Player* playerPtr;

		/// @brief 現在のHP
		int32 currentHP;

		/// @brief ゲームの残り時間
		int32 time{ 300 };

		/// @brief 現在の潤い
		int32 currentMoisture;

		/// @brief カーソルの位置
		Vec2 position{ 0, 0 };
	public:
		UIState(Player* playerPtr);
		~UIState();
		void Update();

		int32 GetCurrentHP();
		int32 GetCurrentMoisture();
		int32 GetTime();
		Vec2 GetPosition() const;
	};
}
