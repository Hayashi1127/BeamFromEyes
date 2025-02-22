﻿# pragma once
# include <Siv3D.hpp>

# include "./View/UIDrawer.hpp"

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	void UIDrawer::Draw()
	{
		modelDatabasePtr->texUpperUI.draw(0, 5);
		modelDatabasePtr->texUnderUI.draw(0, windowSizePtr->y - modelDatabasePtr->texUnderUI.size().y - 5);

		modelDatabasePtr->hpBar.SetSize(windowSizePtr->x/1.5, 40).SetCenter(windowSizePtr->x / 2, 40).draw(uiStatePtr->GetCurrentHP(), uiStatePtr->GetInitialHP());
		modelDatabasePtr->moistureBar.SetCenter(uiStatePtr->GetPosition()).draw(uiStatePtr->GetCurrentMoisture(), uiStatePtr->GetInitialMoisture());

		if (uiStatePtr->GetCurrentHP() <= 0)
		{
			font(U"守りきれませんでした...来世に期待ですね").drawAt(windowSizePtr->x / 2, windowSizePtr->y / 2, Palette::White);
		}
		Circle{ uiStatePtr->GetPosition(), 10 }.draw();
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
