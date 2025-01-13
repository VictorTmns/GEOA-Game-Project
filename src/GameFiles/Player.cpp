#include "PGAUtils.h"
#include "player.h"
#include "SDL_keyboard.h"
#include "structs.h"
#include "utils.h"


Player::Player(const PGAPoint2f& leftBottom, float screenWidth, float screenHeight)
	: m_ScreenWidth{0}
	, m_ScreenHeight{0}
	, m_BulletRadius{0}
	, m_Bounds{ leftBottom, 80, 20}
{
}

void Player::Update(float elapsedSec)
{
	TwoBlade mover{};

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_W]) {
		mover.e31() = 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mover.e31() = -1;
	}
	if (state[SDL_SCANCODE_D]) {
		mover.e23() = 1;
	}
	if (state[SDL_SCANCODE_A]) {
		mover.e23() = -1;
	}

	if (abs(mover.Norm()) <= FLT_EPSILON)
		return;
	Motor translator{ Motor::Translation(500 * elapsedSec, !mover) };

	m_Bounds.leftBottom = (translator * m_Bounds.leftBottom * ~translator).Grade3();
}


void Player::Draw() const
{
	utils::SetColor(Color4f{ 255, 0, 0, 255 });
	utils::FillRect(m_Bounds.leftBottom.x(), m_Bounds.leftBottom.y(), m_Bounds.width, m_Bounds.height);
}

bool Player::IsOverlapping(const PGACirclef& circle) const
{
	return PGAUtils::IsOverlapping(m_Bounds, circle);
}

void Player::SetNewTargetPoint(int x, int y)
{
	m_TargetPoint = ThreeBlade{ static_cast<float>(x), static_cast<float>(y), 0 };
	UpdateMovementDir();
}


void Player::UpdateMovementDir()
{
	m_MovementDir = ThreeBlade{ m_ScreenWidth / 2,  m_ScreenHeight / 2, m_TargetPoint.z() } &m_TargetPoint;
}