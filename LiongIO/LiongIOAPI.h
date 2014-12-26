//defined: /doc /LD /EHa

#pragma once
#include <windows.h>
#include <fstream>
#include "LiongGL\Texture.h"

#pragma comment(lib, "LiongGL.lib")

#pragma warning( disable: 4251 )

using namespace std;

#ifdef LiongIO_Export
#define  _IO_ __declspec(dllexport)
#else
#define _IO_ __declspec(dllimport) 
#endif

#define _LIO_BEGIN		namespace LiongStudio { namespace IO {
#define _LIO_END		} }

typedef unsigned char       byte;
typedef unsigned short      word;
typedef unsigned long       dword;

typedef unsigned int		uint;