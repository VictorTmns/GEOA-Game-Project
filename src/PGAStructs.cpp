#include "PGAStructs.h"

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
PGAPoint2f::PGAPoint2f()
	:PGAPoint2f{ 0.0f, 0.0f }
{
}
PGAPoint2f::PGAPoint2f(float x, float y)
	: PGAPoint2f{ x, y, 0 }

{
}

PGAPoint2f::PGAPoint2f(float x, float y, float z)
	: position{ x, y, z }
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
PGARectf::PGARectf()
	:PGARectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

PGARectf::PGARectf(float left, float bottom, float width, float height)
	:leftBottom{ left, bottom }
	, width{ width }
	, height{ height }
{
}


PGARectf::PGARectf(PGAPoint2f leftBottom, float width, float height)
	:leftBottom{ std::move(leftBottom)}
	, width{ width }
	, height{ height }
{
	
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
PGACirclef::PGACirclef()
	:PGACirclef{ 0.0f, 0.0f, 0.0f }
{
}

PGACirclef::PGACirclef(float centerX, float centerY, float radius)
	:PGACirclef{ PGAPoint2f{ centerX, centerY }, radius }
{
}

PGACirclef::PGACirclef(const PGAPoint2f& center, float radius)
	:center{ center }
	, radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
PGAEllipsef::PGAEllipsef()
	:PGAEllipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}


PGAEllipsef::PGAEllipsef(PGAPoint2f center, float radiusX, float radiusY)
	: center{std::move(center)}
	  , radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

PGAEllipsef::PGAEllipsef(float centerX, float centerY, float radiusX, float radiusY)
	: PGAEllipsef{ PGAPoint2f{ centerX, centerY }, radiusX, radiusY }
{
}
