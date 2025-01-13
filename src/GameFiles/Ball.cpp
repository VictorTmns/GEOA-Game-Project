#include "Ball.h"

#include <iostream>

#include "PGAUtils.h"
#include "Player.h"
#include "SDL_stdinc.h"
#include "utils.h"

Ball::Ball(const PGAPoint2f& startPos, TwoBlade startVelocity, float screenWidth, float screenHeight)
	: m_Bounds{ startPos, 10}
	  , m_ScreenWidth{screenWidth}
	  , m_ScreenHeight{screenHeight}
	  , m_MovementDir{std::move(startVelocity)}
{
}



void Ball::Update(float elapsedSec, const Player& player)
{
	Move(elapsedSec);


	ReflectOnScreenEdge();
	CheckPlayerCollision(player);

	if (m_Bounds.center.y() < 2*m_Bounds.radius)
		m_IsAlive = false;
}

void Ball::Draw() const
{
	utils::SetColor(Color4f{ 0, 0, 255, 255 });
	utils::FillEllipse(m_Bounds.center.x(), m_Bounds.center.y(), m_Bounds.radius, m_Bounds.radius);

	//utils::SetColor(Color4f{ 255, 0, 0, 255 });
	//utils::FillEllipse(m_TargetPoint[0], m_TargetPoint[1], 10, 10);
}





void Ball::Move(float elapsedSec)
{
	Motor translator{ Motor::Translation(500 * elapsedSec, !m_MovementDir) };
	m_Bounds.center = (translator * m_Bounds.center * ~translator).Grade3();
}

//void Ball::Rotate(float elapsedSec)
//{
//	TwoBlade rotatingLine{ TwoBlade::LineFromPoints(m_TargetPoint[0], m_TargetPoint[1], m_TargetPoint[2],
//		m_TargetPoint[0], m_TargetPoint[1], m_TargetPoint[2]+1 )};
//
//	Motor rotator{ Motor::Rotation(100*elapsedSec, rotatingLine) };
//
//
//	m_LeftBottom = (rotator * m_LeftBottom * ~rotator).Grade3();
//}


void Ball::ReflectOnScreenEdge()
{
	if (PGAUtils::Distance(m_Bounds.center, OneBlade{ -m_Bounds.radius, 1, 0, 0 }) < 0)
	{
		m_MovementDir = PGAUtils::Reflect(m_MovementDir, OneBlade{ 0, 1, 0, 0 });
		m_Bounds.center.x() = m_Bounds.radius + 0.1f;
	}

	if (PGAUtils::Distance(m_Bounds.center, OneBlade{ 0 + m_ScreenWidth - m_Bounds.radius, -1, 0, 0 }) < 0)
	{
		m_MovementDir = PGAUtils::Reflect(m_MovementDir, OneBlade{ 0, -1, 0, 0 });
		m_Bounds.center.x() = m_ScreenWidth - m_Bounds.radius - 0.1f;
	}


	if (PGAUtils::Distance(m_Bounds.center, OneBlade{ 0 + m_ScreenHeight - m_Bounds.radius, 0, -1, 0 }) < 0)
	{
		m_MovementDir = PGAUtils::Reflect(m_MovementDir, OneBlade{ 0, 0, -1, 0 });
		m_Bounds.center.y() =  m_ScreenHeight - m_Bounds.radius - 0.1f;
	}
}

void Ball::CheckPlayerCollision(const Player& player)
{
	if (!player.IsOverlapping(m_Bounds))
		return;

	PGAPoint2f playerReflectionPoint{ player.GetBounds().leftBottom };
	playerReflectionPoint.x() += player.GetBounds().width / 2.f;
	playerReflectionPoint.y() += player.GetBounds().height / 2.f;

	m_MovementDir = playerReflectionPoint.position.Normalized() & m_Bounds.center.position.Normalized();
}



void Ball::HandleBlockCollision(const PGARectf& block)
{
	Motor translator{ Motor::Translation(5, !-m_MovementDir) };
	m_Bounds.center = (translator * m_Bounds.center * ~translator).Grade3();

	//Find the reflection plane
	OneBlade reflectionPlane{ CalculateReflectionPlane(block)};

	m_MovementDir = PGAUtils::Reflect(m_MovementDir, reflectionPlane);
}

OneBlade Ball::CalculateReflectionPlane(const PGARectf& block) const
{
	ThreeBlade rotP1 { block.leftBottom.x(), block.leftBottom.y(), 0};
	ThreeBlade rotP11{ block.leftBottom.x(), block.leftBottom.y(), 1};
	ThreeBlade rotP2 { block.leftBottom.x() + block.width, block.leftBottom.y(), 0};
	ThreeBlade rotP22{ block.leftBottom.x() + block.width, block.leftBottom.y(), 1};
	ThreeBlade rotP3 { block.leftBottom.x(), block.leftBottom.y() + block.height, 0};
	ThreeBlade rotP33{ block.leftBottom.x(), block.leftBottom.y() + block.height, 1 };
	ThreeBlade rotP4 { block.leftBottom.x() + block.width, block.leftBottom.y() + block.height, 0 };
	ThreeBlade rotP44{ block.leftBottom.x() + block.width, block.leftBottom.y() + block.height, 1 };


   	TwoBlade rotL1{ rotP1 & rotP11};
	TwoBlade rotL2{ rotP2 & rotP22};
	TwoBlade rotL3{ rotP3 & rotP33};
	TwoBlade rotL4{ rotP4 & rotP44};


	OneBlade leftPlane	{ block.leftBottom.x()					,-1 , 0 , 0 };
	OneBlade rightPlane	{ -(block.leftBottom.x() + block.width)	, 1 , 0 , 0 };
	OneBlade bottomPlane{ block.leftBottom.y()					, 0 ,-1 , 0 };
	OneBlade topPlane	{ -(block.leftBottom.y() + block.height), 0 , 1 , 0 };

	Motor rotator{};


	//Leftbottom plane
	rotator = Motor::Rotation(45, rotL1);
	rotator.Normalize();
	OneBlade pl1{ (rotator * bottomPlane * ~rotator).Grade1() };

	
	//rightbottom plane
	rotator = Motor::Rotation(-45, rotL2);
	rotator.Normalize();
	OneBlade pl2{ (rotator * bottomPlane * ~rotator).Grade1() };


	//topleft plane
	rotator = Motor::Rotation(-45, rotL3);
	rotator.Normalize();
	OneBlade pl3{ (rotator * topPlane * ~rotator).Grade1() };

	//topright plane
	rotator = Motor::Rotation(45, rotL4);
	rotator.Normalize();
	OneBlade pl4{ (rotator * topPlane * ~rotator).Grade1() };


	float d1{ PGAUtils::Distance(m_Bounds.center, pl1) };
	float d2{ PGAUtils::Distance(m_Bounds.center, pl2) };
	float d3{ PGAUtils::Distance(m_Bounds.center, pl3) };
	float d4{ PGAUtils::Distance(m_Bounds.center, pl4) };


	if (PGAUtils::IsInFront(pl1, m_Bounds.center) && PGAUtils::IsInFront(pl2, m_Bounds.center))
		return bottomPlane;

	if (!PGAUtils::IsInFront(pl2, m_Bounds.center) && !PGAUtils::IsInFront(pl4, m_Bounds.center))
		return rightPlane;

	if (!PGAUtils::IsInFront(pl1, m_Bounds.center) && !PGAUtils::IsInFront(pl3, m_Bounds.center))
   		return leftPlane;

	if (PGAUtils::IsInFront(pl3, m_Bounds.center) && PGAUtils::IsInFront(pl4, m_Bounds.center))
		return topPlane;



	std::cout << "error in reflectionPlane searching for ball and block collision";
}