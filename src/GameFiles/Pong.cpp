#include "Pong.h"

#include <iostream>

Pong::Pong( const Rectf& viewPort)
	: m_Player{ PGAPoint2f{100.f, 100.f}, viewPort.width, viewPort.height }
	, m_BallManager{ viewPort.width, viewPort.height }
	, m_Viewport{viewPort}
	, m_BlockManager{ viewPort.width, viewPort.height }
{
	std::cout << "left click: set position pillar \n"
		<< "right click: change pillar \n"
		<< "spacebar: use speedboost";
}

void Pong::Update(float elapsedSec)
{
	m_Player.Update(elapsedSec);
	m_BallManager.Update(elapsedSec, m_Player, m_BlockManager);
	m_BlockManager.Update(elapsedSec);
}

void Pong::Draw() const
{
	m_BlockManager.Draw();
	m_BallManager.Draw();
	m_Player.Draw();
}

void Pong::LeftMouseClick(float x, float y)
{
	m_Player.SetNewTargetPoint(x, y);
}

void Pong::RightMouseClick(float x, float y)
{
	m_Player.SwitchPillars();
}
