#include "Player.h"
#include "utils.h"

Player::Player()
	: m_LeftBottom{200, 200, 0, 1}
{
}

void Player::Update(float elapsedSec)
{
	TwoBlade movementDir{ 1, 0, 0, 0, 0, 0 };
	Motor translator{ Motor::Translation(500 * elapsedSec, movementDir) };

	m_LeftBottom = (translator * m_LeftBottom * ~translator).Grade3();
	m_LeftBottom.Normalize();
}

void Player::Draw() const
{
	utils::FillRect(m_LeftBottom[0], m_LeftBottom[1], 20, 20);
}
