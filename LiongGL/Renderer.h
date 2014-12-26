#pragma once
#include "LiongGLAPI.h"

_LGL_BEGIN
class _GL_ Renderer
{
public:
	static void DrawRectangle(uint textureID, Rectangle rect);
	static void DrawRectangleUpsideDown(uint textureID, Rectangle rect);
	static void DrawBackGroundImage(uint textureID);
};
_LGL_END
