#include "Block.h"

#include "PGAUtils.h"
#include "utils.h"

Block::Block(const PGARectf& bounds)
	: Block{bounds, Color4f{255, 0, 0, 255}}
{
}

Block::Block(PGARectf bounds, const Color4f& color)
	: m_Bounds{std::move(bounds)}
	, m_Color{ color }
{
}

void Block::Draw()
{
	utils::SetColor(m_Color);
	utils::FillRect(m_Bounds.leftBottom.x(), m_Bounds.leftBottom.y(), m_Bounds.width, m_Bounds.height);
}


bool Block::OverlapCheck(const PGACirclef& circle) const
{
	return PGAUtils::IsOverlapping(m_Bounds, circle);
}
