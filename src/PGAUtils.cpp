#include "PGAUtils.h"

#include <iostream>

#include "PGAStructs.h"

bool PGAUtils::PointInsideRect(const PGAPoint2f& point, const PGARectf& rect)
{
	//planes oriented inside
	//checks if the orthogonal distance is smaller then zero
	// if smaller then zero then the point is behind the plane

	if (Distance(point, OneBlade{ -rect.leftBottom.x()				, 1, 0,0}) < 0)
		return false;
	if (Distance(point, OneBlade{ rect.leftBottom.x() + rect.width	,-1, 0,0}) < 0)
		return false;
	if (Distance(point, OneBlade{ -rect.leftBottom.y()				, 0, 1,0}) < 0)
		return false;
	if (Distance(point, OneBlade{ rect.leftBottom.y() + rect.height	, 0,-1,0}) < 0)
		return false;

	return true;
	
}

bool PGAUtils::IsOverlapping(const PGARectf& rect, const PGACirclef& circle)
{
	//4 planes are constructed on the edges of the rectangle, they are oriented outside
	//you check if the distance from the circle its center
	//is smaller then the radius of the circle
	//it this is true for all the planes
	//then the ball is overlapping somewhere on the rect

	if (   Distance(circle.center, OneBlade{ rect.leftBottom.x()					,-1 , 0 , 0 }) < circle.radius
		&& Distance(circle.center, OneBlade{ -(rect.leftBottom.x() + rect.width)	, 1 , 0 , 0 }) < circle.radius
		&& Distance(circle.center, OneBlade{ rect.leftBottom.y()					, 0 ,-1 , 0 }) < circle.radius
		&& Distance(circle.center, OneBlade{ -(rect.leftBottom.y() + rect.height)	, 0 , 1 , 0 }) < circle.radius
		)
		return true;
	return false;
}

bool PGAUtils::IsInFront(const OneBlade& plane, const PGAPoint2f& point)
{
	return(Distance(point, plane) > 0);
}

float PGAUtils::Distance(const PGAPoint2f& point, const OneBlade& plane)
{
	return point.position.Normalized()&plane.Normalized();
}

TwoBlade PGAUtils::Reflect(const TwoBlade& object, const OneBlade& reflectionPlane)
{
	OneBlade refPlaneNormalize{ reflectionPlane.Normalized() };
	TwoBlade objectNormalized{ object.Normalized() };

	const Motor projection{ (objectNormalized | refPlaneNormalize) * refPlaneNormalize };
	const Motor rejection{ (objectNormalized ^ refPlaneNormalize) * refPlaneNormalize };

	const Motor reflection{ projection - rejection };

	return reflection.Grade2();
}
