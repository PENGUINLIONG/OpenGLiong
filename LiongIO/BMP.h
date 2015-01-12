#pragma once
#include "Preprocess.h"
#include "LiongGL\Entrance.h"

using namespace LiongStudio::GL;

_LIO_BEGIN
class _IO_ BMP
{
public:
	static bool InitHeader(ifstream &stream, SIZE &size, int &length);

	static unsigned char *ReadData(ifstream &stream, int length);

	//static GLuint Automatic(ifstream &stream, wchar_t *path);
	static void Automatic(ifstream &stream, wchar_t *path, Texture &texture);
};
_LIO_END
