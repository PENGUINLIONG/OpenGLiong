#include "ioWav.h"

namespace LiongIO
{
	ioWav::ioWav()
	{
	}

	code ioWav::FormatDetect(char* path)
	{
		bool flag = true;
		int header = 0;

		stream.open(path, _IOSbinary | _IOS_Nocreate);
		FileFormat_wav rw;
		Read((char *)&rw, sizeof(FileFormat_wav));
		if (rw.ID != *(DWORD *)"RIFF" && rw.Type != *(DWORD *)"WAVE") flag = false;
		else header += sizeof(FileFormat_wav);

		if (flag)
		{
			MetaData_wav fmt;
			Read((char *)&fmt, sizeof(MetaData_wav));
			if (fmt.ID != *(DWORD *)"fmt ") flag = false;
			else header += sizeof(MetaData_wav);
			while (flag)
			{
				if (stream.eof()) flag = false;
				else ++header;
				char c[4];
				Read(&c[0], 1);
				if (c[0] == 'd')
				{
					Read(&c[1], 3);
					if (c[1] == 'a' && c[2] == 't' && c[3] == 'a') { header += 3; break; }
					else stream.seekg(-3, stream.cur);
				}
			}
		}
		Close();
		if (flag) return header;
		else return IO_BadFormat;
	}

	code ioWav::Prepare(int bufferlength = 131072)
	{
		wfx.cbSize = 0;
		wfx.wFormatTag = WAVE_FORMAT_PCM;
		wfx.nChannels = metadata.Channels;
		wfx.nSamplesPerSec = metadata.SamplesPerSec;
		wfx.nAvgBytesPerSec = metadata.AvgBytesPerSec;
		wfx.nBlockAlign = metadata.BlockAlign;
		wfx.wBitsPerSample = metadata.BitsPerSample;

		agent.Length = bufferlength;
		agent.Stream = &stream;

		return IO_Fine;
	}

	code ioWav::Uncompress()
	{
		return IO_NotImplemented;
	}

	code ioWav::Unprepare()
	{
		wfx = WAVEFORMATEX();
		agent.Length = 0;
		agent.Stream = nullptr;
		return IO_Fine;
	}

	code ioWav::Swap()
	{
		AudioDoubleBuffer &buffer = agent.Buffer;

		if (agent.QuitFlag) return IO_Audio_QuitFlag;

		if (stream.eof()) // Is the stream at the end of file?
		{
			agent.QuitFlag = true; // Let performing thread stop looping.
			return IO_StreamFailure;
		}

		if (useA) // The case of using BufferA.
		{
			if (buffer.PreparedA == true)
				return IO_Audio_NotPlayed;
			stream.read(buffer.BufferA, agent.Length); // Read data into BufferA.
			buffer.CountA = stream.gcount(); // Get the count of bits that stream has read from file.
			buffer.PreparedA = true; // Remind the performing thread that BufferA is ready.
			useA = false; // Remind the next loop to do "the BufferB work".
		}
		else // The case of using BufferB.
		{
			if (buffer.PreparedB == true)
				return IO_Audio_NotPlayed;
			stream.read(buffer.BufferB, agent.Length);
			buffer.CountB = stream.gcount();
			buffer.PreparedB = true;
			useA = true;
		}
		return IO_Fine;
	}

	ioWav::~ioWav()
	{
	}
}