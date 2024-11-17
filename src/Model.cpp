# pragma once
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
