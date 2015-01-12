#pragma once
#include "Preprocess.h"

_LIO_BEGIN
enum class ImageFileFormat
{
	BMP,
	JPEG,
	PNG,
	GIF,
	Undefined
};

class _IO_ ImageFormat
{
public:
	static ImageFileFormat DetectFormat(wchar_t *path);
	static bool AssertFormat(wchar_t *path, ImageFileFormat format);
};
_LIO_END
