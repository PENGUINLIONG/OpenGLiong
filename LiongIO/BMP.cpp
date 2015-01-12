#include "BMP.h"

_LIO_BEGIN
bool BMP::InitHeader(ifstream &stream, SIZE &size, int &length)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	stream.read((char *)&bf, sizeof(BITMAPFILEHEADER));
	stream.read((char *)&bi, sizeof(BITMAPINFOHEADER));
	if (bi.biBitCount != 24)
		return false;
	size = { bi.biWidth, bi.biHeight };
	length = bi.biSizeImage;

	stream.seekg(bf.bfOffBits, stream.beg);
	return true;
}

unsigned char *BMP::ReadData(ifstream &stream, int length)
{
	unsigned char *data = new unsigned char[length]; // NEED TO BE DELETED.
	stream.read((char *)data, length);

	return data;
}
/*
GLuint BMP::Automatic(ifstream &stream, wchar_t *path)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	int width, height;
	int length = InitHeader(stream, width, height);
	unsigned char *data = ReadData(stream, length);
	uint textureID = Texture::Generate2dTexture(width, height, data, length);
	delete [] data;

	return textureID;
}
*/
void BMP::Automatic(ifstream &stream, wchar_t *path, Texture &texture)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	if (InitHeader(stream, texture.Size, texture.DataLength))
	{
		unsigned char *data = ReadData(stream, texture.DataLength);
		texture.Data = data;
		texture.PixelFormat = GL_BGR_EXT;
		texture.ByteSize = GL_UNSIGNED_BYTE;
		texture.Generate();
		texture.Informative = true;
	}
	stream.close();
}
_LIO_END