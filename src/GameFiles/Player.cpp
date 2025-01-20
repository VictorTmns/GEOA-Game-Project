#include "PGAUtils.h"
#include "player.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "structs.h"
#include "utils.h"


Player::Player(const PGAPoint2f& leftBottom, float screenWidth, float screenHeight)
	: m_ScreenWidth{ screenWidth }
	, m_ScreenHeight{ screenHeight }
	, m_Bounds{ leftBottom, 80, 20}
	, m_RotationMult{ 50.f}
{
}

void Player::CheckBounds()
{
	if (m_Bounds.leftBottom.x() < 0 || m_Bounds.leftBottom.x() > m_ScreenWidth - m_Bounds.width
		|| m_Bounds.leftBottom.y() < 0 || m_Bounds.leftBottom.y() > m_ScreenHeight / 2 - m_Bounds.height)
		m_RotationMult *= -1;
}

void Player::Update(float elapsedSec)
{
	Rotate(elapsedSec);
	CheckBounds();

	if (m_Bounds.leftBottom.z() < m_MaxEnergy)
	{
		Motor translator{ Motor::Translation(40.f * elapsedSec, TwoBlade{0, 0, 1, 0, 0, 0}) };
		m_Bounds.leftBottom = (translator * m_Bounds.leftBottom * ~translator).Grade3();
	}
}

void Player::Rotate(float elapsedSec)
{
	float speedBoost{ 1 };

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_SPACE] && m_Bounds.leftBottom.z() > 0)
	{
		speedBoost = 3;
		Motor translator{ Motor::Translation(-300.0f * elapsedSec, TwoBlade{0, 0, 1, 0, 0, 0}) };
		m_Bounds.leftBottom = (translator * m_Bounds.leftBottom * ~translator).Grade3();
	}

	TwoBlade rotatingLine{ TwoBlade::LineFromPoints(m_TargetPoint.x(), m_TargetPoint.y(), m_TargetPoint.z(),
		m_TargetPoint.x(), m_TargetPoint.y(), m_TargetPoint.z() + 1)};

	Motor rotator{ Motor::Rotation(m_RotationMult *elapsedSec * speedBoost, rotatingLine) };

	m_Bounds.leftBottom = (rotator * m_Bounds.leftBottom * ~rotator).Grade3();
}


void Player::Draw() const
{
	utils::SetColor(Color4f{ 1, 0, 0,  1 });
	utils::FillRect(m_Bounds.leftBottom.x(), m_Bounds.leftBottom.y(), m_Bounds.width, m_Bounds.height);
	utils::SetColor(Color4f{ 0, 1, 0,  m_Bounds.leftBottom.z()/m_MaxEnergy });
	utils::FillRect(m_Bounds.leftBottom.x(), m_Bounds.leftBottom.y(), m_Bounds.width, m_Bounds.height);
	utils::SetColor(Color4f{ 1, 1, 1, 1 });
	utils::DrawRect(m_Bounds.leftBottom.x(), m_Bounds.leftBottom.y(), m_Bounds.width, m_Bounds.height);

	//target
	utils::SetColor(Color4f{ 1, 1, 1, 1 });
	utils::FillEllipse(m_TargetPoint.x(), m_TargetPoint.y(), 5, 5);
	utils::SetColor(Color4f{ 0.2f, 0.2f, 0.2f, 1 });
	utils::FillEllipse(m_OtherTarget.x(), m_OtherTarget.y(), 5, 5);
	//screendivider
	utils::SetColor(Color4f{ 1, 0, 1, 1 });
	utils::DrawLine(0, m_ScreenHeight/2, m_ScreenWidth, m_ScreenHeight/2);

}

bool Player::IsOverlapping(const PGACirclef& circle) const
{
	return PGAUtils::IsOverlapping(m_Bounds, circle);
}

void Player::SetNewTargetPoint(int x, int y)
{
	m_OtherTarget = m_TargetPoint;
	m_TargetPoint = ThreeBlade{ static_cast<float>(x), static_cast<float>(y), 0 };
	m_RotationMult *= -1;
}

void Player::SwitchPillars()
{
	PGAPoint2f temp{ m_OtherTarget };
	m_OtherTarget = m_TargetPoint;
	m_TargetPoint = temp;
}
