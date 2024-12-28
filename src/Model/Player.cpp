# pragma once
# include <Siv3D.hpp>

# include "./Model/Player.hpp"

namespace BeamFromEyes::Model
{
	void Player::ReceiveDamage(const int32 enemyAtp)
	{
		hp -= enemyAtp;
	}

	int32 Player::BeamAttack()
	{
		DryMoisture(1);
		return atp;
	}

	void Player::DryMoisture(const int32 dry)
	{
		eyeMoisture -= dry;
	}

	void Player::RecoveryMoisture(const int32 moisture)
	{
		eyeMoisture += moisture;
	}

	int32 Player::GetHP() const
	{
		return hp;
	}

	int32 Player::GetMoisture() const
	{
		return eyeMoisture;
	}

	Player::Player()
	{

	}

	Player::~Player()
	{

	}
}
