#pragma once
# include <Siv3D.hpp>

namespace BeamFromEyes::Model
{
	class CustomShapeProgressBar
	{
	private:

		Polygon m_shape;

		Polygon m_shrinkedShape;

		ColorF m_backgroundColor = ColorF(0.25);

		/// @brief 残量に応じて色を変える
		Array<std::pair<double, ColorF>> m_barColors = {
			{ 1.0, ColorF(0.1, 0.8, 0.2) }
		};

		double m_shearedX = 0.0;

		ColorF getBarColor(double progress) const;
	public:

		CustomShapeProgressBar() = default;

		explicit CustomShapeProgressBar(const Polygon& polygon, double shearedX = 0.0)
			: CustomShapeProgressBar(polygon, ColorF(0.25), { { 1.0, ColorF(0.1, 0.8, 0.2) } }, shearedX) {}

		CustomShapeProgressBar(const Polygon& polygon, const ColorF& backgroundColor, const ColorF& barColor, double shearedX = 0.0)
			: CustomShapeProgressBar(polygon, backgroundColor, { { 1.0, barColor } }, shearedX) {}

		CustomShapeProgressBar(const Polygon& polygon, const ColorF& backgroundColor, const Array<std::pair<double, ColorF>>& barColors, double shearedX = 0.0)
			: m_shape(polygon)
			, m_shrinkedShape(polygon.calculateBuffer(-1))
			, m_backgroundColor(backgroundColor)
			, m_barColors(barColors)
			, m_shearedX(shearedX)
		{
			m_barColors.sort_by([](const auto& a, const auto& b) { return a.first > b.first; });
		}

		// バーを描く
		const CustomShapeProgressBar& draw(double value, double maxValue) const;
	};
}
