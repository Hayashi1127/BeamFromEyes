#pragma once
# include <Siv3D.hpp>

# include "./Model/CircleProgressBar.hpp"

namespace BeamFromEyes::Model
{
	ColorF CircleProgressBar::getBarColor(double progress) const
	{
		ColorF result = barColors.front().second;

		for (auto& c : barColors)
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

	const CircleProgressBar& CircleProgressBar::draw(double value, double maxValue) const
	{
		const double progress = maxValue ? Math::Saturate(value / maxValue) : 1.0;
		const Circle innnerCircle = shape;
		const Circle innnerCircleBar(shape);

		shape.drawArc(Math::ToRadians(360 - angle / 2), Math::ToRadians(angle), 0, thick, backgroundColor);
		innnerCircleBar.drawArc(Math::ToRadians(360 - angle / 2), Math::ToRadians(angle) * progress, 0, thick-2, getBarColor(progress));

		return *this;
	}

	const CircleProgressBar& CircleProgressBar::SetCenter(const double x, const double y)
	{
		shape.setCenter(x, y);
	}

	const CircleProgressBar& CircleProgressBar::SetCenter(const Vec2 pos)
	{
		shape.setCenter(pos);
	}

	const CircleProgressBar& CircleProgressBar::SetRadius(const double r)
	{
		shape.setR(r);
	}

	const CircleProgressBar& CircleProgressBar::SetThick(const int32 t)
	{
		thick = t;
	}
}
