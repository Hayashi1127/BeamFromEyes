# pragma once
# include <Siv3D.hpp>

# include "./Model/BackgroundObject.hpp"
# include "./Model/Obstacle.hpp"
# include "./Model/Player.hpp"
# include "./Model/ModelDatabase.hpp"

# include <Controller.hpp>

using namespace BeamFromEyes::Controller;

namespace BeamFromEyes::Model
{
	class ModelManager
	{
	private:
		/// @brief シーン上の障害物の最大数
		const int8 obstacleMaxNum = 5;

		/// @brief シーン上に障害物が出現する確率
		const float obstacleAppearanceRate = 0.005;

		/// @brief コントローラ―の入力を受け取るためのクラスへのポインタ
		const ControllerManager* controllerManagerPtr;

		/// @brief 背景描画に必要なクラスへのポインタ
		BackgroundObject* backgroundObjectPtr;

		/// @brief プレイヤー
		Player* playerPtr;

		/// @brief 障害物たち
		Array<Obstacle> obstacles;
	public:
		ModelManager(const ControllerManager* controller);
		~ModelManager();
		const BackgroundObject* GetBackgroundObjectPtr() const;
		const Array<Obstacle>* GetObstaclePtr() const;
		void Update();
	};
}
