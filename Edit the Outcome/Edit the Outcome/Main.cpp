# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Common.hpp"
# include "BootScene.hpp"
# include "TitleScene.hpp"
# include "BattleScene.hpp"

void Main()
{
	// ウィンドウサイズを設定
	const int32 windowWidth{ 1280 };
	const int32 windowHeight{ 720 };
	// ウィンドウ状態を設定
	const bool isFullscreen{ false };

	// スクリーンサイズ変更
	Scene::Resize(windowWidth, windowHeight);

	// ウィンドウサイズを変更
	Window::Resize(windowWidth, windowHeight);

	// スクリーン状態を設定
	Window::SetFullscreen(isFullscreen);

	// 背景色を黒に設定
	Scene::SetBackground(Palette::Black);

	// フォント名を定義
	FontAsset::Register(U"TitleFont", 30, Typeface::Medium);
	FontAsset::Register(U"BattleSystem", 30, Typeface::Medium);
	FontAsset::Register(U"HUD", 18, Typeface::Regular);
	FontAsset::Register(U"Command", 20, Typeface::Regular);

	// シーン管理マネージャーの生成
	ProjectApp manager;

	// シーンを登録
	manager.add<BootScene>(State::BootScene);
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
