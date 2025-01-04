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

	Vec2 UIState::GetPosition() const
	{
		return position;
	}

	void UIState::Update()
	{
		this->currentHP = playerPtr->GetHP();
		this->currentMoisture = playerPtr->GetMoisture();

		Vec3 pos3 = playerPtr->GetPosition();
		this->position.x = pos3.x;
		this->position.y = pos3.y;

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
