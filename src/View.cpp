# pragma once

# include <Model.hpp>
# include <View.hpp>
# include <Controller.hpp>

using namespace BeamFromEyes::Controller;
using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	void ViewManager::Update()
	{
		Graphics3D::SetCameraTransform(mainCamera);
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundDrawerPtr->GetBackgroundColor()) };

		backgroundDrawerPtr->Draw();
		obstacleDrawerPtr->Draw();

		// 3D -> 2D変換
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);

		// ポストプロセス
		// postprocessPtr->Process(renderTexture);

		renderTexture.draw();
	}

	ViewManager::ViewManager(const ModelManager* model)
	{
		monitorInfos = System::EnumerateMonitors();
		windowSize = System::GetCurrentMonitor().fullscreenResolution;
		Window::SetFullscreen(true);
		Window::SetTitle(U"Beam For Eyes");

		modelManagerPtr = model;

		backgroundDrawerPtr = new BackgroundDrawer(modelManagerPtr->GetBackgroundObjectPtr(), &modelDatabase);
		obstacleDrawerPtr = new ObstacleDrawer(modelManagerPtr->GetObstaclePtr(), &modelDatabase);
		postprocessPtr = new PostProcess(&windowSize);
	}

	ViewManager::~ViewManager()
	{
		delete(backgroundDrawerPtr);
		delete(obstacleDrawerPtr);
		delete(postprocessPtr);
	}
}
