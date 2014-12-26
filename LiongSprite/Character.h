#pragma once
#include <math.h>
#include "LiongSpriteAPI.h"
#include "LiongGL\Texture.h"
#include "LiongGL\Renderer.h"

using namespace LiongStudio::GL;

_LSPRITE_BEGIN
enum class CharacterDisplayMode {
	Normal,
	UpsideDown,
	Hidden
};

enum class CharacterFX {
	Normal,
	Shaky,
	Flowing,
	Abnormal,
	ExAbnormal,
	ExExAbnormal //////////////////////Need Implementation.//////////////////////
	// Accessory
	/*Intimate,
	Joyful,
	Jetting,*/

};

class _Sprite_ Character
{
public:
	Character();
	void BindTexture(uint textureIndex);
	void ResetGeology(Position position, Size size); // 重置角色立绘“地形”（即位置和大小）
	void SwitchDisplayMode(CharacterDisplayMode displayMode);
	void SwitchFX(CharacterFX fx);
	void SetAlpha(unsigned char alpha);
	bool isAvailable();
	void Render();
	~Character();
private:
	bool available = true;
	unsigned char alpha = 255;
	short fxCounter = 0;
	uint textureIndex;
	Size size;
	Position position;
	Position position_Original;
	CharacterDisplayMode displayMode;
	CharacterFX fx;

	void ProcessFX();
};
_LSPRITE_END
