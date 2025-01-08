#include "Player.h"

#include <iostream>

#include "PGAUtils.h"
#include "utils.h"

Player::Player(float screenWidth, float screenHeight)
	: m_LeftBottom{200, 200, 0, 1}
	, m_TargetPoint{500, 500, 0}
	, m_ScreenWidth{screenWidth}
	, m_ScreenHeight{screenHeight}
	, m_MovementDir{ ThreeBlade{ m_ScreenWidth / 2,  m_ScreenHeight / 2, 0 } & m_TargetPoint }
{

}

void Player::Move(float elapsedSec)
{
	Motor translator{ Motor::Translation(50 * elapsedSec, !m_MovementDir) };

	m_LeftBottom = (translator * m_LeftBottom * ~translator).Grade3();
}

void Player::Rotate(float elapsedSec)
{
	TwoBlade rotatingLine{ TwoBlade::LineFromPoints(m_TargetPoint[0], m_TargetPoint[1], m_TargetPoint[2],
		m_TargetPoint[0], m_TargetPoint[1], m_TargetPoint[2]+1 )};

	Motor rotator{ Motor::Rotation(100*elapsedSec, rotatingLine) };


	m_LeftBottom = (rotator * m_LeftBottom * ~rotator).Grade3();
}



void Player::Update(float elapsedSec)
{
	Move(elapsedSec);
	//Rotate(elapsedSec);
	if (PGAUtils::PointInsideRect(m_LeftBottom, Rectf{0.f, 0.f, m_ScreenWidth, m_ScreenHeight}))
		std::cout << "inside \n";
	else
		std::cout << "outside \n";
}

void Player::Draw() const
{
	utils::SetColor(Color4f{ 0, 0, 255, 255 });
	utils::FillRect(m_LeftBottom[0], m_LeftBottom[1], 20, 20);

	utils::SetColor(Color4f{ 255, 0, 0, 255 });
	utils::FillEllipse(m_TargetPoint[0], m_TargetPoint[1], 10, 10);
}

void Player::SetNewTargetPoint(int x, int y)
{
	m_TargetPoint = ThreeBlade{ static_cast<float>(x), static_cast<float>(y), 0 };
	UpdateMovementDir();
}


void Player::UpdateMovementDir()
{
	m_MovementDir = ThreeBlade{ m_ScreenWidth / 2,  m_ScreenHeight / 2, 0 } &m_TargetPoint;
}

