#pragma once
#include "LiongIOAPI.h"

_LIO_BEGIN
class _IO_ Storage
{
public:
	Storage();
	void Open(char *path);
	void Read(char *buffer, int length);
	void Write(char *buffer, int length);
	bool Exists();
	void Create(char *path);
	void Close();
	~Storage();
protected:
	char *path = nullptr;
	fstream stream;
};
_LIO_END
