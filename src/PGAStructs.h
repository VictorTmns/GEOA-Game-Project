#pragma once
#include "FlyFish.h"

struct PGAPoint2f
{
	PGAPoint2f();
	explicit PGAPoint2f(float x, float y);
	explicit PGAPoint2f(float x, float y, float z);


	PGAPoint2f& operator=(ThreeBlade&& other) {
		position = std::move(other);
		return *this;
	}

	operator ThreeBlade() const {return position;}

	const float& y() const { return position.e013(); }
	const float& x() const { return position.e032(); }
	const float& z() const { return position.e021(); }
	float& y() { return position.e013(); }
	float& x() { return position.e032(); }
	float& z() { return position.e021(); }
	ThreeBlade position;
};



struct PGARectf
{
	PGARectf();
	explicit PGARectf(float left, float bottom, float width, float height);
	explicit PGARectf(PGAPoint2f leftBottom, float width, float height);

	PGAPoint2f leftBottom;
	float width;
	float height;

};



struct PGACirclef
{
	PGACirclef();
	explicit PGACirclef(const PGAPoint2f& center, float radius);
	explicit PGACirclef(float centerX, float centerY, float radius);

	PGAPoint2f center;
	float radius;
};


struct PGAEllipsef
{
	PGAEllipsef();
	explicit PGAEllipsef(PGAPoint2f center, float radiusX, float radiusY);
	explicit PGAEllipsef(float centerX, float centerY, float radiusX, float radiusY);

	PGAPoint2f center;
	float radiusX;
	float radiusY;
};