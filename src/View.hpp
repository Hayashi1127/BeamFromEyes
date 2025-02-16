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

	public:
		ViewManager(const ModelManager* model);
		~ViewManager();
		void Update();
	};
}
