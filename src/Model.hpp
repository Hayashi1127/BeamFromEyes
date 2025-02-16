# pragma once
# include <Siv3D.hpp>

# include "./Model/BackgroundObject.hpp"
# include "./Model/Obstacle.hpp"
# include "./Model/Player.hpp"
# include "./Model/ModelDatabase.hpp"
# include "./Model/UIState.hpp"

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

		/// @brief UI描画用情報
		UIState* uiStatePtr;

		/// @brief ゲーム画面の大きさ
		Size windowSize{ 1920, 1080 };

		/// @brief ゲーム画面の2D描画先
		const MSRenderTexture renderTexture{ windowSize, TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

		/// @brief ゲーム画面のメインカメラ
		BasicCamera3D mainCamera{ windowSize, 30_deg, Vec3{ 0, 0, -10} };

		/// @brief スタート(1)、ゲーム(2)、リザルト(3)
		int8 sceneFlag = 0;

		/// @brief 接続されているモニターの情報
		Array<MonitorInfo> monitorInfos;
	public:
		ModelManager(const ControllerManager* controller);
		~ModelManager();
		const BackgroundObject* GetBackgroundObjectPtr() const;
		const Array<Obstacle>* GetObstaclePtr() const;
		const UIState* GetUIStatePtr() const;
		void Update();

		const Size* GetWindowSizePtr() const;
		const MSRenderTexture GetRenderTexture() const;
		const BasicCamera3D GetCamera() const;
		const int8* GetSceneFlagPtr() const;
	};
}
