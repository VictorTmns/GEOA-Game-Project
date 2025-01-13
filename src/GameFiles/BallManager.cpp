#include "BallManager.h"

#include <algorithm>

#include "SDL_keyboard.h"

BallManager::BallManager(float screenWidth, float screenHeight)
	: m_ScreenWidth{screenWidth}
	, m_ScreenHeight{screenHeight}
{
	AddBall(PGAPoint2f{ 30.f, 30.f }, TwoBlade{ 0, 0, 0, float(std::rand() % 20) - 10, 10, 0.f });
}


void BallManager::AddBall(const PGAPoint2f& startPos, const TwoBlade& startVelocity)
{
	m_Balls.push_back(std::make_unique<Ball>(startPos, startVelocity, m_ScreenWidth, m_ScreenHeight));
}

void BallManager::Update(float elapsedSec, const Player& player, BlockManager& blockManager)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_SPACE])
	{
		AddBall(PGAPoint2f{ 30.f, 30.f }, TwoBlade{ 0, 0, 0, float(std::rand() % 20) - 10, 10, 0.f });
	}


	std::erase_if(m_Balls, [](auto& ball)
		{return !ball->IsAlive();});

	std::ranges::for_each(m_Balls, [elapsedSec, &player](auto& ball)
		{ball->Update(elapsedSec, player);});


	std::ranges::for_each(m_Balls, [&blockManager](auto& ball)
		{blockManager.DoCollisions(*ball); });
}

void BallManager::Draw() const
{
	for (auto& ball : m_Balls)
	{
		ball->Draw();
	}
}
