# include <Siv3D.hpp> // Siv3D v0.6.15
# include <ExpressionApp.hpp>

// My Library
# include <Model.hpp>
# include <View.hpp>
# include <Controller.hpp>

using namespace BeamForEyes::Model;
using namespace BeamForEyes::View;
using namespace BeamForEyes::Controller;

void Main()
{
	// int expressionAppReturn = ExpressionApp();

	ControllerManager controller;
	ModelManager model{ &controller };
	ViewManager view{ &model, &controller };

	while (System::Update())
	{
		model.Update();
		view.Update();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
