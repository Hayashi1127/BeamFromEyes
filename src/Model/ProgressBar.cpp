#pragma once
# include <Siv3D.hpp>

# include "./Model/ProgressBar.hpp"

namespace BeamFromEyes::Model
{
	ColorF ProgressBar::getBarColor(double progress) const
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

	const ProgressBar& ProgressBar::draw(double value, double maxValue) const
	{
		const double progress = maxValue ? Math::Saturate(value / maxValue) : 1.0;
		const RectF innnerRect = m_rect.stretched(-1);
		const RectF innnerRectBar(innnerRect.pos, innnerRect.w * progress, innnerRect.h);

		if (m_round == 0.0)
		{
			m_rect.draw(m_backgroundColor);
			innnerRectBar.draw(getBarColor(progress));
		}
		else
		{
			m_rect.rounded(m_round).draw(m_backgroundColor);

			if (innnerRectBar.w)
			{
				const Polygon bar = innnerRectBar.asPolygon();
				const RoundRect innnerRoundRect = innnerRect.rounded(m_round - 1);
				const Polygon clip = innnerRoundRect.asPolygon();

				if (const auto g = Geometry2D::And(bar, clip))
				{
					g.front().draw(getBarColor(progress));
				}
			}
		}

		return *this;
	}

	ProgressBar& ProgressBar::SetCenter(const double x, const double y)
	{
		m_rect.setCenter(x, y);
		return *this;
	}

	ProgressBar& ProgressBar::SetCenter(const Vec2 pos)
	{
		m_rect.setCenter(pos);
		return *this;
	}

	ProgressBar& ProgressBar::SetSize(const double w, const double h)
	{
		m_rect.setSize(w, h);
		return *this;
	}

	ProgressBar& ProgressBar::SetSize(const Size size)
	{
		m_rect.setSize(size);
		return *this;
	}
}
