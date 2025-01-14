#pragma once
#include "PGAstructs.h"


class Player
{
public:
	Player(const PGAPoint2f& leftBottom, float screenWidth, float screenHeight);

	void Update(float elapsedSec);
	void Draw() const;

	void SetNewTargetPoint(int x, int y);
	void SwitchPillars();

	bool IsOverlapping(const PGACirclef& circle) const;

	PGARectf GetBounds() const { return m_Bounds; };
private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;
	const float m_MaxEnergy = 200;

	PGARectf m_Bounds;
	PGAPoint2f m_TargetPoint;
	PGAPoint2f m_OtherTarget;
	float m_RotationMult;



	void Rotate(float elapsedSec);
	void CheckBounds();
};
