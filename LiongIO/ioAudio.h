#pragma once

#include "ioStorage.h"
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

namespace LiongIO
{
	interface ioAudio : public ioStorage
	{
	public:
		virtual _IO_ code DetectFormat(char* path) = 0;
		virtual _IO_ code Prepare(int length) = 0;
		virtual _IO_ code Uncompress() = 0;
		virtual _IO_ code Unprepare() = 0;
		virtual _IO_ code Swap() = 0;
		_IO_ code Open(char* path) override final;
		_IO_ code Write(char* buffer, int length) override final;
		_IO_ code Create(char* path) override final;

		const char* type;
	protected:
		WAVEFORMATEX wfx;
		AudioAgent agent;
		int header = 0;
		bool useA = true;
	};
}

#define IO_Audio_NotPlayed					-8
#define IO_Audio_QuitFlag					-9
//#define ...								...
//#define IO_Audio_xxx						-15