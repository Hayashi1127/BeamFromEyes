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
		Graphics3D::SetCameraTransform(modelManagerPtr->GetCamera());
		MSRenderTexture renderTexture = modelManagerPtr->GetRenderTexture();
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundDrawerPtr->GetBackgroundColor())};

		backgroundDrawerPtr->Draw();
		obstacleDrawerPtr->Draw();

		// 3D -> 2D変換
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);

		// ポストプロセス
		// postprocessPtr->Process(renderTexture);

		renderTexture.draw();

		uiDrawerPtr->Draw();
	}

	ViewManager::ViewManager(const ModelManager* model)
	{
		modelManagerPtr = model;

		backgroundDrawerPtr = new BackgroundDrawer(modelManagerPtr->GetBackgroundObjectPtr(), &modelDatabase);
		obstacleDrawerPtr = new ObstacleDrawer(modelManagerPtr->GetObstaclePtr(), &modelDatabase);
		uiDrawerPtr = new UIDrawer(modelManagerPtr->GetUIStatePtr(), &modelDatabase, modelManagerPtr->GetWindowSizePtr());
		postprocessPtr = new PostProcess(modelManagerPtr->GetWindowSizePtr());
	}

	ViewManager::~ViewManager()
	{
		delete(backgroundDrawerPtr);
		delete(obstacleDrawerPtr);
		delete(uiDrawerPtr);
		delete(postprocessPtr);
	}
}
