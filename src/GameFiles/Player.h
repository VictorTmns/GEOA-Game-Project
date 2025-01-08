#pragma once
#include "FlyFish.h"
#include "structs.h"

class Player
{
public:
	Player(float screenWidth, float ScreenHeight);

	~Player() = default;

	void Update(float elapsedSec);
	void Draw() const;


	void SetNewTargetPoint(int x, int y);
	void UpdateMovementDir();
	bool IsInsideBounds(const Rectf& bounds);

private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;

private:
	ThreeBlade m_LeftBottom;
	ThreeBlade m_TargetPoint;
	TwoBlade m_MovementDir;


	void Move(float elapsedSec);
	void Rotate(float elapsedSec);
};
