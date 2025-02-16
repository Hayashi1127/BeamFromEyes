# pragma once
# include <Siv3D.hpp>

# include <Model.hpp>
# include "./Model/UIState.hpp"

using namespace BeamFromEyes::Model;

namespace BeamFromEyes::View
{
	class UIDrawer
	{
	private:
		const UIState* uiStatePtr;
		const ModelDatabase* modelDatabasePtr;
		const Size* windowSizePtr;

		// 画面に何か文字表示したい時に使う
		const Font font{ 50 };
	public:
		UIDrawer(const UIState* uiStatePtr,const ModelDatabase* modelDatabasePtr, const Size* sizePtr);
		~UIDrawer();
		void Draw();
	};
}
