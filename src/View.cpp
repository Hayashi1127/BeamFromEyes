# pragma once

# include <Model.hpp>
# include <View.hpp>
# include <Controller.hpp>

using namespace BeamForEyes::Controller;
using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	void ViewManager::Update()
	{
		Graphics3D::SetCameraTransform(mainCamera);
		const ScopedRenderTarget3D target{ renderTexture.clear(backgroundDrawerPtr->GetBackgroundColor()) };

		backgroundDrawerPtr->Draw();

		// 3D -> 2D変換
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);

		// ポストプロセス
		// postprocessPtr->Process(renderTexture);

		renderTexture.draw();
	}

	ViewManager::ViewManager(const ModelManager* model, const ControllerManager* controller)
	{
		modelManagerPtr = model;
		controllerManagerPtr = controller;

		backgroundDrawerPtr = new BackgroundDrawer(modelManagerPtr->GetBackgroundObjectPtr());
		postprocessPtr = new PostProcess(&windowSize);

		Window::Resize(windowSize);
		Window::SetTitle(U"Beam For Eyes");
	}

	ViewManager::~ViewManager()
	{
	}
}
