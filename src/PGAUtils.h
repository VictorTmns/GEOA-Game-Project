#pragma once
#include "FlyFish.h"
#include "PGAStructs.h"
#include "structs.h"

class PGAUtils
{
public:
	static bool PointInsideRect(const PGAPoint2f& point, const PGARectf& rect);

	static bool IsOverlapping(const PGARectf& rect, const PGACirclef& circle);

	static bool IsInFront(const OneBlade& plane, const PGAPoint2f& point);

	static float Distance(const PGAPoint2f& point, const OneBlade& plane);


	static TwoBlade Reflect(const TwoBlade& object, const OneBlade& reflectionPlane);

};