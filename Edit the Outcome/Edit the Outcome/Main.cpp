# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Common.hpp"
# include "TitleScene.hpp"
# include "BattleScene.hpp"

void Main()
{
	FontAsset::Register(U"TitleFont", 30, Typeface::Medium);
	FontAsset::Register(U"BattleSystem", 30, Typeface::Medium);

	ProjectApp manager;
	manager.add<TitleScene>(State::TitleScene);
	manager.add<BattleScene>(State::BattleScene);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
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
