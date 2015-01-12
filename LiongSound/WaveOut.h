#pragma once
#include "Preprocess.h"

_LSOUND_BEGIN
class _Sound_ WaveOut
{
public:
	WaveOut();
	void Write(char *buffer, unsigned int bufferLength, PCMFormat fmt, bool loop);
	void Write(char *buffer, unsigned int bufferLength, PCMFormat fmt);
	void Reset();
	void Pause();
	void Restart();
	static void CALLBACK Callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	~WaveOut();
private:
	bool loop = true;
	bool playing = false;
	char *buffer;
	unsigned int bufferLength;
	WAVEFORMATEX waveFormatEx;
	HWAVEOUT hWaveOut;
	WAVEHDR waveHDR;

	void Init(PCMFormat fmt);
	void Write();
};
_LSOUND_END