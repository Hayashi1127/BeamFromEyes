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
		playerPtr->Update();
		uiStatePtr->Update();

		const Vec3 p = playerPtr->GetPosition();
		const Ray ray = mainCamera.screenToRay({ p.x, p.y });
		for (int i=0 ; i<obstacles.size() ; i++)
		{
			const Optional<float> distance = ray.intersects(obstacles.at(i).GetCollider());
			if (distance.has_value())
			{
				obstacles.at(i).ReceiveDamage(playerPtr->BeamAttack());
				if (obstacles.at(i).GetHP() <= 0)
				{
					obstacles.erase(obstacles.begin() + i);
				}
				i--;
			}
		}

		// 自陣に到達した敵について、プレイヤーへの攻撃後削除
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles.at(i).IsReached())
			{
				playerPtr->ReceiveDamage(obstacles.at(i).Attack());
				obstacles.erase(obstacles.begin() + i);
				i--;
			}
			else
			{
				obstacles.at(i).Update();
			}
		}

		// 敵の生成
		if (obstacles.isEmpty() || (obstacles.size() < obstacleMaxNum && RandomBool(obstacleAppearanceRate)))
		{
			obstacles.push_back(Obstacle());
		}
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
