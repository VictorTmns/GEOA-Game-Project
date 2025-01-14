#include "BlockManager.h"
#include "array"

BlockManager::BlockManager(float screenWidth, float screenHeight)
{
	constexpr int nrWidth{8};
	constexpr int nrHeight{10};
	constexpr float margin{10};
	 
	const float blockWidth{( screenWidth - margin) / nrWidth - margin };
	const float blockHeight{ (screenHeight/2 - margin) / nrHeight - margin };
	for (int i = 0; i < nrWidth; ++i)
	{
		float x{ ((screenWidth - margin) / nrWidth )* i + margin };
		for (int j = 0; j < nrHeight; ++j)
		{
			float y{ screenHeight - blockHeight - (((screenHeight/2 - margin) / nrHeight) * j + margin) };

			AddBlock(x, y, blockWidth, blockHeight);
		}
	}
}

constexpr std::array<Color4f, 10> BlockColors = {
Color4f{1, 0, 0, 1},
Color4f{0, 1, 0, 1},
Color4f{0, 0, 1, 1},
Color4f{1, 1, 0, 1},
Color4f{0, 1, 1, 1},
Color4f{1, 0, 1, 1},
Color4f{1, 0.33f, 0, 1},
Color4f{0.5f, 0, 0.5f, 1},
Color4f{0, 0.5f, 0.5f, 1},
Color4f{0.5f, 0.5f, 0.5f, 1}
};

void BlockManager::AddBlock(float x, float y, float width, float height)
{
	int colorIdx{ std::rand() % 10 };


	m_Blocks.push_back(std::make_unique<Block>(PGARectf{ x, y, width, height }, BlockColors[colorIdx]));
}
void BlockManager::DoCollisions(Ball& ball)
{
	for (auto& block : m_Blocks)
	{
		if (block->OverlapCheck(ball.GetBounds()))
		{
			block->SetDead();
			SpawnReward(block->Center());

			ball.HandleBlockCollision(block->GetBounds());
		}
	}
}

void BlockManager::Update(float elapsedSec)
{
	std::erase_if(m_Blocks, [](auto& block)
		{return !block->IsAlive(); });
}

void BlockManager::Draw() const
{
	for (auto& block : m_Blocks)
	{
		block->Draw();
	}
}



void BlockManager::SpawnReward(const PGAPoint2f& pos)
{
}