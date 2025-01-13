#pragma once
#include "PGAStructs.h"
#include "structs.h"

class Block
{
public:
	Block(PGARectf bounds, const Color4f& color);
	Block(const PGARectf& bounds);

	void Draw();

	bool OverlapCheck(const PGACirclef& circle) const;
	void SetDead() { m_IsAlive = false; }
	bool IsAlive() { return m_IsAlive; }


	PGAPoint2f Center() const
	{
		return PGAPoint2f{
		m_Bounds.leftBottom.x() + m_Bounds.width,
		m_Bounds.leftBottom.y() + m_Bounds.height };
	}
	const PGARectf& GetBounds() { return m_Bounds; }
private:
	const Color4f m_Color;

	bool m_IsAlive = true;
	PGARectf m_Bounds;

};
