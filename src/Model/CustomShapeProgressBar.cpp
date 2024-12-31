# pragma once
# include <Siv3D.hpp>

# include "./Model/CustomShapeProgressbar.hpp"

namespace BeamFromEyes::Model
{
	ColorF CustomShapeProgressBar::getBarColor(double progress) const
	{
		ColorF result = m_barColors.front().second;

		for (auto& c : m_barColors)
		{
			if (progress < c.first)
			{
				result = c.second;
			}
			else
			{
				break;
			}
		}

		return result;
	}

	const CustomShapeProgressBar& CustomShapeProgressBar::draw(double value, double maxValue) const
	{
		const double progress = maxValue ? Math::Saturate(value / maxValue) : 1.0;
		const RectF innnerRect = m_shrinkedShape.boundingRect();
		const RectF innnerRectBar(innnerRect.pos, innnerRect.w * progress, innnerRect.h);

		if (m_shearedX == 0.0)
		{
			m_shape.draw(m_backgroundColor);

			if (innnerRectBar.w)
			{
				const Polygon bar = innnerRectBar.asPolygon();

				if (const auto g = Geometry2D::And(bar, m_shrinkedShape))
				{
					g.front().draw(getBarColor(progress));
				}
			}
		}
		else
		{
			const Vec2 center = m_shape.boundingRect().center();
			Transformer2D tr(Mat3x2::Translate(-center).shearedX(m_shearedX).translated(center));

			m_shape.draw(m_backgroundColor);

			if (innnerRectBar.w)
			{
				const Polygon bar = innnerRectBar.asPolygon();

				if (const auto g = Geometry2D::And(bar, m_shrinkedShape))
				{
					g.front().draw(getBarColor(progress));
				}
			}
		}

		return *this;
	}
}
