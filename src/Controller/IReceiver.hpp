# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::Controller
{
	class IReceiver
	{
	private:
		Vec3 location;
	public:
		virtual ~IReceiver();
		virtual void GetLocation();
	};
}
