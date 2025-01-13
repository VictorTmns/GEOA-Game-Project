#pragma once
#include "FlyFish.h"
#include "PGAStructs.h"
#include "Player.h"
#include "structs.h"

class Ball
{
public:
	Ball(const PGAPoint2f& startPos, TwoBlade startVelocity, float screenWidth, float screenHeight);


	void Update(float elapsedSec, const Player& player);
	void Draw() const;

	void HandleBlockCollision(const PGARectf& rect);
	OneBlade CalculateReflectionPlane(const PGARectf& block) const;

	bool IsAlive() const { return m_IsAlive; }
	const PGACirclef& GetBounds() const { return m_Bounds; }
private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;

	PGACirclef m_Bounds;
	TwoBlade m_MovementDir;


	bool m_IsAlive = true;

	void Move(float elapsedSec);
	void ReflectOnScreenEdge();
	void CheckPlayerCollision(const Player& player);
};
