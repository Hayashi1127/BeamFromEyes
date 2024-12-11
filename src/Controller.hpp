# pragma once

# include "./Controller/MousePointerReceiver.hpp"
# include "./Controller/EyetrackingReceiver.hpp"
# include "./Controller/IPointerReceiver.hpp"
# include "./Controller/KeyboardReceiver.hpp"

namespace BeamForEyes::Controller
{
	class ControllerManager
	{
	private:
		IPointerReceiver* pointerReceiverPtr = nullptr;
	public:
		ControllerManager();
		~ControllerManager();
		void Update();
		const IPointerReceiver* GetPointerReceiverPtr() const;
	};
}
