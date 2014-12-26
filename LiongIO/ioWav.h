#pragma once

#include "ioAudio.h"

namespace LiongIO
{
	typedef struct tagFileFormat_wav
	{
		DWORD ID; // RIFF as default
		DWORD Size;
		DWORD Type; // WAVE as default
	} FileFormat_wav; // Part of riff wave file.

	typedef struct tagMetaData_wav
	{
		DWORD ID; // Always be fmt[space]
		DWORD Size; // The length of the structure. (Excluding ID and Size)
		WORD FormatTag; // 0x0001 as default.
		WORD Channels; // The number of channels: 1->Mono; 2->Stereo
		DWORD SamplesPerSec;
		DWORD AvgBytesPerSec;
		WORD BlockAlign; // (Length of each block of data)
		WORD BitsPerSample; // (width of PCM sample)
	} MetaData_wav; // Part of riff wave file.

	class ioWav : public ioAudio
	{
	public:
		const char* type = "WAVE";
		ioWav();
		code FormatDetect(char* path) override final;
		code Prepare(int length) override final;
		code Uncompress() override final;
		code Unprepare() override final;
		code Swap() override final;
		~ioWav();
	private:
		MetaData_wav metadata;
	};
}