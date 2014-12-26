#include "ioAudio.h"
namespace LiongIO
{
	code ioAudio::Open(char* path)
	{
		int h = DetectFormat(path);
		if (h < IO_Fine) return h; // Check state.
		stream.open(path, _IOSbinary | _IOS_Nocreate);
		stream.seekg(h, stream.beg);
		this->path = path;
		this->header = h;
		return h;
	}

	code ioAudio::Write(char* buffer, int length)
	{
		return IO_NotImplemented;
	}

	code ioAudio::Create(char* path)
	{
		return IO_NotImplemented;
	}
}