#include "ImageFormat.h"

_LIO_BEGIN
ImageFileFormat ImageFormat::DetectFormat(wchar_t *path)
{
	ifstream stream;
	stream.open(path);
	__int32 tag;
	stream.read((char *)&tag, 4);
	if ((tag & 0xFFFF0000) == 0x424D0000)
		return ImageFileFormat::BMP;
	switch (tag)
	{
	case 0xFFD8FFE0: return ImageFileFormat::JPEG;
	case 0x89504E47: return ImageFileFormat::PNG;
	case 0x47494638: return ImageFileFormat::GIF;
	}
	return ImageFileFormat::Undefined;
}

bool ImageFormat::AssertFormat(wchar_t *path, ImageFileFormat format)
{
	return DetectFormat(path) == format;
}

/*
void ImageFormat::Open()
{
	if (!path)
		throw "Class is not initialized.";
	if (stream.is_open())
		stream.close();
	if (Exists(path))
		stream.open(path, stream.binary | stream._Nocreate | stream._Noreplace);
}

bool ImageFormat::Exists(char *path)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, _IOS_Nocreate | _IOS_Noreplace);
	if (stream.is_open()) { stream.close(); return true; }
	else return false;
}

void ImageFormat::Close()
{
	stream.close();
}*/
_LIO_END
