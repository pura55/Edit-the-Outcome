#include "stdafx.h"
#include "CharacterRenderer.hpp"

CharacterRenderer::CharacterRenderer()
{
}

void CharacterRenderer::update()
{
	
}

/// <remarks>
/// 描画に関する注意点を記述します。
///
/// アトラステクスチャーを描画する際にRect の変数を .uv() に渡すと、
/// ピクセルではなく割合（0.0〜1.0）として誤認識されてしまう可能性があるため
/// 今後描画する際は(Rect{})で代用してください。
/// 
/// </remarks>
void CharacterRenderer::draw() const
{
	/// プレイヤー ///
	{
		 TextureAsset(U"Swordsman")(m_playerAtRegion).draw(m_playerPos);
	}
}
