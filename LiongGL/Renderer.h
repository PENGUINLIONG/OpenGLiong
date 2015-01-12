#pragma once
#include "Preprocess.h"

_LGL_BEGIN
class _GL_ Renderer
{
public:
	Renderer();
	void DrawRectangle(GLuint textureID, RECTD rect);
	void DrawRectangleUpsideDown(GLuint textureID, RECTD rect);
	void DrawBackGroundImage(GLuint textureID);
	void DrawWithoutTexture(RECTD rect);
	void Resize(SIZE size);
	~Renderer();
private:
	SIZE window;
};
_LGL_END
