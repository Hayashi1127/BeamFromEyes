# pragma once
# include <Siv3D.hpp>

# include "./Model/UIState.hpp"

namespace BeamFromEyes::Model
{
	int32 UIState::GetCurrentHP()
	{
		return currentHP;
	}

	int32 UIState::GetCurrentMoisture()
	{
		return currentMoisture;
	}

	int32 UIState::GetTime()
	{
		return time;
	}

	void UIState::Update()
	{
		this->currentHP = playerPtr->GetHP();
		this->currentMoisture = playerPtr->GetMoisture();

		time--;
	}

	UIState::UIState(Player* playerPtr)
	{
		this->playerPtr = playerPtr;
		this->currentHP = playerPtr->GetHP();
		this->currentMoisture = playerPtr->GetMoisture();
	}

	UIState::~UIState()
	{

	}
}
