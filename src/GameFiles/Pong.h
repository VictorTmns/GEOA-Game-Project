#pragma once
#include "BallManager.h"
#include "BlockManager.h"

class Pong
{
public:
	Pong(const Rectf& viewport);
	~Pong() = default;

	void Update(float elapsedSec);
	void Draw() const;

private:
	Player m_Player;
	BallManager m_BallManager;
	BlockManager m_BlockManager;
	Rectf m_Viewport;
};
