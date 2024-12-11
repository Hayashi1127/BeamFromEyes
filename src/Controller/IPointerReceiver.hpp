# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Controller
{
	class IPointerReceiver
	{
	public:
		virtual void Update() = 0; 
		virtual Vec2 GetPointerPosition() = 0;
		virtual bool GetIsPressed() = 0;
	};
}
