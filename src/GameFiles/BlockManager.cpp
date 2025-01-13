#include "BlockManager.h"


BlockManager::BlockManager()
{
	AddBlock(PGAPoint2f{ 300, 500 });
}


void BlockManager::AddBlock(const PGAPoint2f& startPos)
{
	m_Blocks.push_back(std::make_unique<Block>(PGARectf{ startPos, 100, 100 }));
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