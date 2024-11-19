# pragma once

# include "./View/BackgroundDrawer.hpp"
# include "./View/ObstacleDrawer.hpp"
# include "./View/PostProcess.hpp"
# include "./View/UIDrawer.hpp"

# include <Model.hpp>
# include <Controller.hpp>

using namespace BeamForEyes::Controller;
using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	class ViewManager
	{
	private:
		const ModelManager* modelManagerPtr;
		const ControllerManager* controllerManagerPtr;

		/// @brief モデルデータベース
		const ModelDatabase modelDatabase;

		// 各描画用クラスへのポインタ
		BackgroundDrawer* backgroundDrawerPtr = nullptr;
		ObstacleDrawer* obstacleDrawerPtr = nullptr;
		PostProcess* postprocessPtr = nullptr;

		/// @brief ゲーム画面の大きさ
		const Size windowSize = Size{ 1280, 720 };

		/// @brief ゲーム画面の2D描画先
		const MSRenderTexture renderTexture{ windowSize, TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

		/// @brief ゲーム画面のメインカメラ
		BasicCamera3D mainCamera{ windowSize, 30_deg, Vec3{ 0, 0, -10} };

	public:
		ViewManager(const ModelManager* model, const ControllerManager* controller);
		~ViewManager();
		void Update();
	};
}
