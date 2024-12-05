# pragma once

# include "./Controller/EyetrackingReceiver.hpp"
# include "./Controller/IReceiver.hpp"
# include "./Controller/KeyboardReceiver.hpp"

namespace BeamForEyes::Controller
{
	class ControllerManager
	{
	private:
	public:
		ControllerManager();
		~ControllerManager();
		void Update();
	};
}
