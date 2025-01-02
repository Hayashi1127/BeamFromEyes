#pragma once
# include <Siv3D.hpp>

namespace BeamFromEyes::Model
{
	class ProgressBar
	{
	private:
		RectF m_rect = RectF(0);

		ColorF m_backgroundColor = ColorF(0.25);

		/// @brief 残量に応じて色を変える
		Array<std::pair<double, ColorF>> m_barColors = {
			{ 1.0, ColorF(0.1, 0.8, 0.2) }
		};

		/// @brief 角を丸める
		double m_round = 0.0;

		/// @brief 引数の数字に応じて適切なバーの色を返す
		ColorF getBarColor(double progress) const;
	public:

		ProgressBar() = default;

		explicit ProgressBar(const RectF& rect, double round = 0.0)
			: ProgressBar(rect, ColorF(0.25), { { 1.0, ColorF(0.1, 0.8, 0.2) } }, round) {}

		ProgressBar(const RectF& rect, const ColorF& backgroundColor, const ColorF& barColor, double round = 0.0)
			: ProgressBar(rect, backgroundColor, { { 1.0, barColor } }, round) {}

		ProgressBar(const RectF& rect, const ColorF& backgroundColor, const Array<std::pair<double, ColorF>>& barColors, double round = 0.0)
			: m_rect(rect)
			, m_backgroundColor(backgroundColor)
			, m_barColors(barColors)
			, m_round(round)
		{
			m_barColors.sort_by([](const auto& a, const auto& b) { return a.first > b.first; });
		}

		/// @brief バーを描く
		const ProgressBar& draw(double value, double maxValue) const;

		/// @brief 中心座標を変更する
		const ProgressBar& SetCenter(const double x, const double y);

		const ProgressBar& SetCenter(const Vec2 pos);

		/// @brief サイズを変更する
		const ProgressBar& SetSize(const double w, const double h);

		const ProgressBar& SetSize(const Size size);
	};
}
