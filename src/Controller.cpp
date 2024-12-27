# pragma once
# include <Controller.hpp>

namespace BeamFromEyes::Controller
{
	void ControllerManager::Update()
	{
		pointerReceiverPtr->Update();
	}

	const IPointerReceiver* ControllerManager::GetPointerReceiverPtr() const
	{
		return pointerReceiverPtr;
	}

	ControllerManager::ControllerManager()
	{
		pointerReceiverPtr = new MousePointerReceiver();
	}

	ControllerManager::~ControllerManager()
	{
		delete(pointerReceiverPtr);
	}
}
