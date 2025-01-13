#pragma once
#include <list>
#include <memory>
#include "Block.h"
#include "Ball.h"

class BlockManager
{
public:
	BlockManager();
	void AddBlock(const PGAPoint2f& startPos);

	void DoCollisions(Ball& ball);

	void Update(float elapsedSec);
	void Draw() const;
private:
	std::list<std::unique_ptr<Block>> m_Blocks;

	


	void SpawnReward(const PGAPoint2f& pos);
};
