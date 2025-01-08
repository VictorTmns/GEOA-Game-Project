#pragma once
#include "FlyFish.h"
#include "structs.h"

class PGAUtils
{
public:
	static bool PointInsideRect(const ThreeBlade& point, const Rectf& rect);
	

	static float Distance(const ThreeBlade& point, const OneBlade& plane);


	static TwoBlade Reflect(const TwoBlade& object, const ThreeBlade& reflectionPlane);

};