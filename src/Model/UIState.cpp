# pragma once
# include <Siv3D.hpp>

# include "./Model/UIState.hpp"

namespace BeamFromEyes::Model
{
	int32 UIState::GetInitialHP() const
	{
		return initialHP;
	}

	int32 UIState::GetCurrentHP() const
	{
		return currentHP;
	}

	int32 UIState::GetInitialMoisture() const
	{
		return initialMoisture;
	}

	int32 UIState::GetCurrentMoisture() const
	{
		return currentMoisture;
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
	}

	UIState::UIState(Player* playerPtr)
	{
		this->playerPtr = playerPtr;
		this->initialHP = playerPtr->GetHP();
		currentHP = initialHP;
		this->initialMoisture = playerPtr->GetMoisture();
		currentMoisture = initialMoisture;
	}

	UIState::~UIState()
	{

	}
}
