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
		return draw(this->shape, value, maxValue);
	}

	const CircleProgressBar& CircleProgressBar::draw(const Circle shape, double value, double maxValue) const
	{
		const double progress = maxValue ? Math::Saturate(value / maxValue) : 1.0;
		const Circle innnerCircle = shape;
		const Circle innnerCircleBar(shape);

		shape.drawArc(Math::ToRadians(360 - angle/2), Math::ToRadians(angle), 0, 7, backgroundColor);
		innnerCircleBar.drawArc(Math::ToRadians(360 - angle / 2), Math::ToRadians(angle)*progress, 0, 5, getBarColor(progress));

		return *this;
	}
}
