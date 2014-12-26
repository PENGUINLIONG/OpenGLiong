#pragma once
#include "LiongIOAPI.h"
#include "LiongSound\WaveOut.h"

using namespace LiongStudio::Sound;

_LIO_BEGIN
typedef struct {
	DWORD RIFF;
	DWORD Length;
	DWORD WAVE;
} RIFFWaveHeaderChunk;

typedef struct {
	DWORD Size;
	WORD FormatTag;
	WORD Channels;
	DWORD SamplesPerSec;
	DWORD AvgBytesPerSec;
	WORD BlockAlign;
	WORD BitsPerSample;
} RIFFWaveFormatChunk;

typedef struct {
	DWORD Size;
	char *Data;
} RIFFWaveDataChunk;

class _IO_ WAV
{
public:
	WAV();
	void ReadData(ifstream *stream, wchar_t *path);
	void SelectFromTo(unsigned int offset, unsigned int duration);
	void Dispose();
	char *GetSelected();
	unsigned int GetSelectedLength();
	PCMFormat GetPCMFormat();
	~WAV();
private:
	bool available;
	unsigned int offset = 0;
	unsigned int endpoint = 0;
	ifstream *pStream;
	RIFFWaveHeaderChunk header;
	RIFFWaveFormatChunk format;
	RIFFWaveDataChunk data;

	void InitHeader();
};
_LIO_END