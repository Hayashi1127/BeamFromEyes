# pragma once
# include <Controller.hpp>

namespace BeamFromEyes::Controller
{
	void ControllerManager::Update()
	{
		// mousePointerReceiverPtr->Update();
		eyetrackingReceiverPtr->Update();
	}

	const IPointerReceiver* ControllerManager::GetPointerReceiverPtr() const
	{
		return pointerReceiverPtr;
	}

	ControllerManager::ControllerManager()
	{
		// mousePointerReceiverPtr = new MousePointerReceiver();
		eyetrackingReceiverPtr = new EyetrackingReceiver();

		pointerReceiverPtr = eyetrackingReceiverPtr;
	}

	ControllerManager::~ControllerManager()
	{
		// delete(mousePointerReceiverPtr);
		delete(eyetrackingReceiverPtr);

		pointerReceiverPtr = nullptr;
	}
}
