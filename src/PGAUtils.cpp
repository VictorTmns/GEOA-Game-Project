#include "PGAUtils.h"

bool PGAUtils::PointInsideRect(const ThreeBlade& point, const Rectf& rect)
{
	if (Distance(point, OneBlade{ -rect.left, 1, 0, 0 }) < 0)
		return false;
	if (Distance(point, OneBlade{ rect.left + rect.width, -1, 0, 0 }) < 0)
		return false;
	if (Distance(point, OneBlade{ -rect.bottom, 0, 1, 0 }) < 0)
		return false;
	if (Distance(point, OneBlade{ rect.bottom + rect.height, 0, -1, 0 }) < 0)
		return false;

	return true;
	
}

float PGAUtils::Distance(const ThreeBlade& point, const OneBlade& plane)
{
	return point.Normalized()&plane.Normalized();
}

TwoBlade PGAUtils::Reflect(const TwoBlade& object, const ThreeBlade& reflectionPlane)
{
	return object;
}
