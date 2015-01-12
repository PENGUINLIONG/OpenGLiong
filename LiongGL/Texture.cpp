#include "Texture.h"

_LGL_BEGIN
Texture::Texture()
{
}
Texture::Texture(GLuint textureIndex)
{
	Index = textureIndex;
	available = true;
}

int Texture::GetPixelLength()
{
	if (ByteSize == GL_UNSIGNED_BYTE)
	{
		switch (PixelFormat)
		{
			case GL_BGR_EXT:
			case GL_RGB:
				return 3;
			case GL_RGBA:
			case GL_BGRA_EXT:
				return 4;
			default: break;
		}
	}
	else if (ByteSize == GL_UNSIGNED_SHORT)
	{
		switch (PixelFormat)
		{
			case GL_RGB:
				return 6;
			case GL_RGBA:
				return 8;
			default: break;
		}
	}
	return 0;
}

void Texture::Generate()
{
	if (!PixelFormat || !Size.cx || !Size.cy || !PixelFormat || !ByteSize || !Data)
		return;
	GLuint textureIndex;

	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Before
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Size.cx, Size.cy, 0, PixelFormat, ByteSize, Data); // After
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Index = textureIndex;
}

Texture::~Texture()
{
	if (Data && available)
	{
		delete[] Data;
		Data = nullptr;
		available = false;
	}
}
_LGL_END