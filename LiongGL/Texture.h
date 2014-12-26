#pragma once
#include "LiongGLAPI.h"

_LGL_BEGIN
typedef struct {
	uint textureID;
	uint textureIndex;
} TextureDictionary;

class _GL_ Texture
{
public:
	//Sign up for a opengl texture index.
	static uint Bind2dTexture(int width, int height, char* data, int length);
};
_LGL_END
