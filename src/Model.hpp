# pragma once
# include <Siv3D.hpp>

# include "./Model/BackgroundObject.hpp"
# include "./Model/Obstacle.hpp"
# include "./Model/Player.hpp"

# include <Controller.hpp>

using namespace BeamForEyes::Controller;

namespace BeamForEyes::Model
{
	class ModelManager
	{
	private:
		/// @brief コントローラ―の入力を受け取るためのオブジェクト
		const ControllerManager* controllerManagerPtr;

		/// @brief 背景描画に必要なオブジェクト
		BackgroundObject* backgroundObjectPtr;

		/// @brief プレイヤー
		Player* playerPtr;

		/// @brief 障害物たち
		Array<Obstacle> obstacles;
	public:
		ModelManager(const ControllerManager* controller);
		~ModelManager();
		const BackgroundObject* GetBackgroundObjectPtr() const;
	};
}
