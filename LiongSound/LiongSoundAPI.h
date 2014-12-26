#pragma once
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#ifdef LiongSound_Export
#define _Sound_ __declspec(dllexport)
#else
#define _Sound_ __declspec(dllimport)
#endif

typedef int code;

#define _LSOUND_BEGIN namespace LiongStudio { namespace Sound {
#define _LSOUND_END } }

typedef struct {
	WORD Channels; // The number of channels: 1->Mono; 2->Stereo
	DWORD SamplesPerSec;
	DWORD AvgBytesPerSec;
	WORD BlockAlign; // (Length of each block of data)
	WORD BitsPerSample; // (width of PCM sample)
} PCMFormat;