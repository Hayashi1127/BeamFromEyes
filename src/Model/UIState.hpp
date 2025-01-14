#pragma once
# include <Siv3D.hpp>

#include "./Model/Player.hpp"

namespace BeamFromEyes::Model
{
	class UIState
	{
	private:
		const Player* playerPtr;

		/// @brief HPの初期値
		int32 initialHP;

		/// @brief 現在のHP
		int32 currentHP;

		/// @brief 潤いの初期値
		int32 initialMoisture;

		/// @brief 現在の潤い
		int32 currentMoisture;

		/// @brief カーソルの位置
		Vec2 position{ 0, 0 };
	public:
		UIState(Player* playerPtr);
		~UIState();
		void Update();

		int32 GetInitialHP() const;
		int32 GetCurrentHP() const;
		int32 GetInitialMoisture() const;
		int32 GetCurrentMoisture() const;
		Vec2 GetPosition() const;
	};
}
