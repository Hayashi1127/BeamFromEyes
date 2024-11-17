# pragma once

# include <Siv3D.hpp>

# include <Model.hpp>

using namespace BeamForEyes::Model;

namespace BeamForEyes::View
{
	class BackgroundDrawer
	{
	private:
		const BackgroundObject* backgroundObjectPtr;

	public:
		BackgroundDrawer(const BackgroundObject* ptr);
		void Draw();
		ColorF GetBackgroundColor() const;
	};
}
