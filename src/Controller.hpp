# pragma once

# include "./Controller/MousePointerReceiver.hpp"
# include "./Controller/EyetrackingReceiver.hpp"
# include "./Controller/IPointerReceiver.hpp"
# include "./Controller/KeyboardReceiver.hpp"

namespace BeamFromEyes::Controller
{
	class ControllerManager
	{
	private:
		MousePointerReceiver* mousePointerReceiverPtr = nullptr;

		EyetrackingReceiver* eyetrackingReceiverPtr = nullptr;

		IPointerReceiver* pointerReceiverPtr = nullptr;

	public:
		ControllerManager();
		~ControllerManager();
		void Update();
		const IPointerReceiver* GetPointerReceiverPtr() const;
	};
}
