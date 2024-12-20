﻿# pragma once
# include <Siv3D.hpp>

# include <Model.hpp>
# include <Controller.hpp>

using namespace BeamForEyes::Controller;

namespace BeamForEyes::Model
{
	const BackgroundObject* ModelManager::GetBackgroundObjectPtr() const
	{
		return backgroundObjectPtr;
	}

	const Array<Obstacle>* ModelManager::GetObstaclePtr() const
	{
		return &obstacles;
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
	}

	ModelManager::ModelManager(const ControllerManager* controller)
	{
		controllerManagerPtr = controller;

		backgroundObjectPtr = new BackgroundObject();
		playerPtr = new Player();

		obstacles.clear();
	}

	ModelManager::~ModelManager()
	{
		delete(backgroundObjectPtr);
		delete(playerPtr);
	}
}
