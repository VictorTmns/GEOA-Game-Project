#pragma once
#include "FlyFish.h"

class Player
{
public:
	Player();

	~Player() = default;

	void Update(float elapsedSec);
	void Draw() const;

private:
	ThreeBlade m_LeftBottom;
};
