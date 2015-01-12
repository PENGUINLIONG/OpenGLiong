#pragma once
#include "Preprocess.h"

_LGL_BEGIN
class _GL_ Texture
{
public:
	bool Informative = false;
	int DataLength;
	unsigned char *Data = nullptr;
	GLuint Index;
	SIZE Size;
	WORD PixelFormat, ByteSize;

	Texture();
	Texture(GLuint textureIndex);
	int GetPixelLength();
	void Generate();
	~Texture();
private:
	bool available = false;
};
_LGL_END
