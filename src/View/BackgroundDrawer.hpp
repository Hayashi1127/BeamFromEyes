﻿# pragma once

# include <Siv3D.hpp>

# include <Model.hpp>

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	class BackgroundDrawer
	{
	private:
		const BackgroundObject* backgroundObjectPtr;
		const ModelDatabase* modelDatabasePtr;

	public:
		BackgroundDrawer(const BackgroundObject* objPtr, const ModelDatabase* databasePtr);
		void Draw();
		ColorF GetBackgroundColor() const;
	};
}
