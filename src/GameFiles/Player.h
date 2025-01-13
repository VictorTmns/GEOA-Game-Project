#pragma once
#include "FlyFish.h"
#include "PGAstructs.h"


class Player
{
public:
	Player(const PGAPoint2f& leftBottom, float screenWidth, float screenHeight);

	void Update(float elapsedSec);
	void Draw() const;

	bool IsOverlapping(const PGACirclef& circle) const;

	PGARectf GetBounds() const { return m_Bounds; };
private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;
	const float m_BulletRadius;

	PGARectf m_Bounds;
	PGAPoint2f m_TargetPoint;
	TwoBlade m_MovementDir;


	void SetNewTargetPoint(int x, int y);
	void UpdateMovementDir();
};
