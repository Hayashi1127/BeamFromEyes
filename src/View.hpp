# pragma once

# include "./View/BackgroundDrawer.hpp"
# include "./View/ObstacleDrawer.hpp"
# include "./View/PostProcess.hpp"
# include "./View/UIDrawer.hpp"

# include <Model.hpp>
# include <Controller.hpp>

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	class ViewManager
	{
	private:
		const ModelManager* modelManagerPtr;

		/// @brief モデルデータベース
		const ModelDatabase modelDatabase;

		// 各描画用クラスへのポインタ
		BackgroundDrawer* backgroundDrawerPtr = nullptr;
		ObstacleDrawer* obstacleDrawerPtr = nullptr;
		UIDrawer* uiDrawerPtr = nullptr;
		PostProcess* postprocessPtr = nullptr;

		/// @brief ゲーム画面の大きさ
		Size windowSize{ 1920, 1080 };

		/// @brief ゲーム画面の2D描画先
		const MSRenderTexture renderTexture{ windowSize, TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

		/// @brief ゲーム画面のメインカメラ
		BasicCamera3D mainCamera{ windowSize, 30_deg, Vec3{ 0, 0, -10} };

		/// @brief スタート(1)、ゲーム(2)、リザルト(3)
		int8 SceneFlag = 0;

		/// @brief 接続されているモニターの情報
		Array<MonitorInfo> monitorInfos;
	public:
		ViewManager(const ModelManager* model);
		~ViewManager();
		void Update();
	};
}
