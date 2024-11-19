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
		const ModelDatabase* modelDatabasePtr;

	public:
		BackgroundDrawer(const BackgroundObject* ptr, const ModelDatabase* ptr2);
		void Draw();
		ColorF GetBackgroundColor() const;
	};
}
