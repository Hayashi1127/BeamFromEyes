# pragma once
# include <Siv3D.hpp>

# include"./View/UIDrawer.hpp"

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	void UIDrawer::Draw()
	{
		modelDatabasePtr->texUpperUI.draw(0, 5);
		modelDatabasePtr->texUnderUI.draw(0, windowSizePtr->y - modelDatabasePtr->texUnderUI.size().y - 5);
	}

	UIDrawer::UIDrawer(const UIState* uiStatePtr, const ModelDatabase* modelDatabasePtr, const Size* sizePtr)
	{
		this->uiStatePtr = uiStatePtr;
		this->modelDatabasePtr = modelDatabasePtr;
		windowSizePtr = sizePtr;
	}

	UIDrawer::~UIDrawer()
	{

	}
}
