#include "BMP.h"

_LIO_BEGIN
int BMP::InitHeader(ifstream &stream, int &width, int &height)
{
	BITMAPFILEHEADER bf;
	stream.read((char *)&bf, sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER bi;
	stream.read((char *)&bi, sizeof(BITMAPINFOHEADER));
	width = bi.biWidth;
	height = bi.biHeight;
	
	stream.seekg(bf.bfOffBits, stream.beg);

	return bi.biSizeImage;
}

char *BMP::ReadData(ifstream &stream, int length)
{
	char *data = new char[length]; // NEED TO BE DELETED.
	stream.read(data, length);

	return data;
}

uint BMP::Automatic(ifstream &stream, wchar_t *path)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	int width, height;
	int length = InitHeader(stream, width, height);
	char *data = ReadData(stream, length);
	uint textureID = Texture::Bind2dTexture(width, height, data, length);
	delete [] data;

	return textureID;
}
_LIO_END
