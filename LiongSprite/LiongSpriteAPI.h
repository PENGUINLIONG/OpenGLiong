//defined: /doc /LD /EHa

#pragma once
#include <windows.h>
#include <list>
#include <LiongGL\LiongGLAPI.h>

#pragma comment(lib, "LiongGL.lib")

#pragma warning( disable: 4251 )

using namespace std;

#ifdef LiongSprite_Export
#define  _Sprite_ __declspec(dllexport)
#else
#define _Sprite_ __declspec(dllimport) 
#endif

#define _LSPRITE_BEGIN		namespace LiongStudio { namespace Sprite {
#define _LSPRITE_END		} }

typedef unsigned int		uint;