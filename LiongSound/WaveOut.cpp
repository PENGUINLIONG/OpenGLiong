#include "WaveOut.h"

_LSOUND_BEGIN
WaveOut::WaveOut()
{
}

void WaveOut::Init(PCMFormat fmt)
{
	waveFormatEx.cbSize = 0;
	waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	waveFormatEx.nChannels = fmt.Channels;
	waveFormatEx.nSamplesPerSec = fmt.SamplesPerSec;
	waveFormatEx.nAvgBytesPerSec = fmt.AvgBytesPerSec;
	waveFormatEx.nBlockAlign = fmt.BlockAlign;
	waveFormatEx.wBitsPerSample = fmt.BitsPerSample;

	waveOutOpen(&hWaveOut, WAVE_MAPPED, &waveFormatEx, (DWORD_PTR)Callback, (DWORD_PTR)this, CALLBACK_FUNCTION);
}

void WaveOut::Write(char *buffer, unsigned int bufferLength, PCMFormat fmt)
{
	Init(fmt);
	if (playing)
		Reset();
	waveHDR.lpData = buffer;
	waveHDR.dwBufferLength = bufferLength;
	waveHDR.dwFlags = waveHDR.dwLoops = 0;
	waveOutPrepareHeader(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	playing = true;
}

void WaveOut::Reset()
{
	waveOutReset(hWaveOut);
	waveOutBreakLoop(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	playing = false;
}

void WaveOut::Pause()
{
	waveOutPause(hWaveOut);
	playing = false;
}

void WaveOut::Callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	//if (uMsg != WOM_DONE)
		//return;
	//WaveOut instance = *(WaveOut *)dwInstance;
	//instance.Reset();
}

WaveOut::~WaveOut()
{
	Reset();
	waveOutClose(hWaveOut);
}
_LSOUND_END