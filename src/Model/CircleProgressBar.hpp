#pragma once
# include <Siv3D.hpp>

namespace BeamFromEyes::Model
{
	class CircleProgressBar
	{
	private:
		Circle shape;

		ColorF backgroundColor = ColorF(0.25);

		/// @brief 残量に応じて色を変える
		Array<std::pair<double, ColorF>> barColors = {
			{ 1.0, ColorF(0.1, 0.8, 0.2) }
		};

		/// @brief バーの描画したい角度
		int32 angle;

		int32 thick;

		ColorF getBarColor(double progress) const;
	public:

		CircleProgressBar() = default;

		explicit CircleProgressBar(const Circle& shape, int32 angle)
			: CircleProgressBar(shape, ColorF(0.75), { { 1.0, ColorF(0.1, 0.8, 0.2) } }, angle) {}

		CircleProgressBar(const Circle& shape, const ColorF& backgroundColor, const ColorF& barColor, int32 angle)
			: CircleProgressBar(shape, backgroundColor, { { 1.0, barColor } }, angle) {}

		CircleProgressBar(const Circle& shape, const ColorF& backgroundColor, const Array<std::pair<double, ColorF>>& barColors, int32 angle)
			: shape(shape)
			, backgroundColor(backgroundColor)
			, barColors(barColors)
			, angle(angle)
		{
			this->barColors.sort_by([](const auto& a, const auto& b) { return a.first > b.first; });
		}

		/// @brief バーを描く
		const CircleProgressBar& draw(double value, double maxValue) const;

		/// @brief 中心座標を変更する
		const CircleProgressBar& SetCenter(const double x, const double y);

		const CircleProgressBar& SetCenter(const Vec2 pos);

		/// @brief サイズを変更する
		const CircleProgressBar& SetRadius(const double r);

		const CircleProgressBar& SetThick(const int32 t);
	};
}
