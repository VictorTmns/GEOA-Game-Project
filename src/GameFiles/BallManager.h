#pragma once
#include <list>

#include "Ball.h"
#include "BlockManager.h"
#include "Player.h"


class BallManager
{
public:
	BallManager(float screenWidth, float screenHeight);
	~BallManager() = default;

	void AddBall(const PGAPoint2f& startPos, const TwoBlade& startVelocity);

	void Update(float elapsedSec, const Player& player, BlockManager& blockManager);
	void Draw() const;


private:
	const float m_ScreenWidth;
	const float m_ScreenHeight;

	int m_NrOfLivesUsed = 0;

	std::list<std::unique_ptr<Ball>> m_Balls;
};
