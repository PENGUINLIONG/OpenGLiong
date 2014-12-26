#pragma once
#include "LiongSoundAPI.h"

_LSOUND_BEGIN
class _Sound_ WaveOut
{
public:
	WaveOut();
	void Write(char *buffer, unsigned int bufferLength, PCMFormat fmt);
	void Reset();
	void Pause();
	static void CALLBACK Callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	~WaveOut();
private:
	bool playing = false;
	WAVEFORMATEX waveFormatEx;
	HWAVEOUT hWaveOut;
	WAVEHDR waveHDR;

	void Init(PCMFormat fmt);
};
_LSOUND_END