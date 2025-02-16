# pragma once
# include <Siv3D.hpp>

# include <Model.hpp>
# include <Controller.hpp>

using namespace BeamFromEyes::Controller;

namespace BeamFromEyes::Model
{
	const BackgroundObject* ModelManager::GetBackgroundObjectPtr() const
	{
		return backgroundObjectPtr;
	}

	const Array<Obstacle>* ModelManager::GetObstaclePtr() const
	{
		return &obstacles;
	}

	const UIState* ModelManager::GetUIStatePtr() const
	{
		return uiStatePtr;
	}

	const Size* ModelManager::GetWindowSizePtr() const
	{
		return &windowSize;
	}

	const MSRenderTexture ModelManager::GetRenderTexture() const
	{
		return renderTexture;
	}

	const BasicCamera3D ModelManager::GetCamera() const
	{
		return mainCamera;
	}

	const int8* ModelManager::GetSceneFlagPtr() const
	{
		return &sceneFlag;
	}

	void ModelManager::Update()
	{
		// 自陣に到達した敵について、プレイヤーへの攻撃後削除
		for (auto it = obstacles.begin() ; it != obstacles.end(); )
		{
			if (it->IsReached())
			{
				// ここに攻撃処理
				it = obstacles.erase(it);
			}
			else
			{
				it->Update();
				it++;
			}
		}

		// 敵の生成
		if (obstacles.isEmpty() || (obstacles.size() < obstacleMaxNum && RandomBool(obstacleAppearanceRate)))
		{
			obstacles.push_back(Obstacle());
		}

		playerPtr->Update();
		uiStatePtr->Update();
	}

	ModelManager::ModelManager(const ControllerManager* controller)
	{
		monitorInfos = System::EnumerateMonitors();
		windowSize = System::GetCurrentMonitor().fullscreenResolution;
		Window::SetFullscreen(true);
		Window::SetTitle(U"Beam For Eyes");

		controllerManagerPtr = controller;

		backgroundObjectPtr = new BackgroundObject();
		playerPtr = new Player(controllerManagerPtr->GetPointerReceiverPtr());
		uiStatePtr = new UIState(playerPtr);

		obstacles.clear();
	}

	ModelManager::~ModelManager()
	{
		delete(backgroundObjectPtr);
		delete(uiStatePtr);
		delete(playerPtr);
	}
}
