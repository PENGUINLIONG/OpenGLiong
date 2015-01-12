#include "WAV.h"

_LIO_BEGIN
WAV::WAV()
{
	data.Data = nullptr;
}

void WAV::InitHeader()
{
	DWORD tag;
	offset = 12;

	pStream->read((char *)&header, sizeof(RIFFWaveHeaderChunk));
	if (header.RIFF != 0x46464952 || header.WAVE != 0x45564157) // 'RIFF' 'WAVE'
		return;

	pStream->read((char *)&tag, sizeof(DWORD));
	if (tag == 0x20746D66) // 'fmt '
	{
		format.Size = 0;
		pStream->read((char *)&format, sizeof(RIFFWaveFormatChunk));
		if (format.Size > 16)
			pStream->seekg(format.Size - 16, pStream->cur);
		offset += format.Size + 8;
	}
	else return;

	pStream->read((char *)&tag, sizeof(DWORD));
	if (tag == 0x74636166) // 'fact'
	{
		DWORD size;
		pStream->read((char *)&size, sizeof(DWORD));
		pStream->seekg(size, pStream->cur);
		pStream->read((char *)&tag, sizeof(DWORD));
		offset += size + 12;
	}

	if (tag == 0x61746164) // 'data'
	{
		pStream->read((char *)&data, sizeof(DWORD));
		offset += 8;
	}
	else return;

	if (data.Data == nullptr)
		data.Data = new char[data.Size];

	available = true;
}

void WAV::ReadData(ifstream *stream, wchar_t *path)
{
	Dispose();

	if (stream->is_open())
		stream->close();
	stream->open(path, stream->binary | stream->_Nocreate);
	this->pStream = stream;

	InitHeader();
	stream->seekg(offset, stream->beg);
	stream->read(data.Data, data.Size);
	
	offset = 0;
	endpoint = data.Size;
	available = true;
}

void WAV::SelectFromTo(unsigned int offsetTime, unsigned int duration)
{
	offset = (format.BitsPerSample * format.SamplesPerSec * format.Channels * offsetTime) >> 3;
	if (duration == 0)
	{
		endpoint = data.Size - 1;
		return;
	}
	
	endpoint = offset + ((format.BitsPerSample * format.SamplesPerSec * format.Channels * duration) >> 3);
}

void WAV::Dispose()
{
	delete [] data.Data;
	available = false;
}

char *WAV::GetSelected()
{
	if (available)
		return data.Data + offset;
	else return nullptr;
}

unsigned int WAV::GetSelectedLength()
{
	return endpoint - offset;
}

PCMFormat WAV::GetPCMFormat()
{
	return{ format.Channels, format.SamplesPerSec, format.AvgBytesPerSec, format.BlockAlign, format.BitsPerSample };
}

WAV::~WAV()
{
	Dispose();
}
_LIO_END