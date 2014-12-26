//defined: /doc /LD /EHa

#pragma once
#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

//#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

#pragma warning( disable: 4251 )

using namespace std;

#ifdef LiongGL_Export
#define  _GL_ __declspec(dllexport)
#else
#define _GL_ __declspec(dllimport) 
#endif

#define _LGL_BEGIN		namespace LiongStudio { namespace GL {
#define _LGL_END		} }

typedef unsigned int	uint;

_LGL_BEGIN
typedef struct {
	double Width;
	double Height;
} Size;

typedef struct {
	double X;
	double Y;
} Position;

typedef struct {
	double Left;
	double Top;
	double Right;
	double Bottom;
} Rectangle;
_LGL_END
