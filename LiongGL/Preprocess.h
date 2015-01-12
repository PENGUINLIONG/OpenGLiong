#pragma once
#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "CommonDeclear.h"

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

_LGL_BEGIN
typedef struct {
	double width;
	double height;
} SIZED;

typedef struct {
	double x;
	double y;
} POINTD;

typedef struct {
	double left;
	double top;
	double right;
	double bottom;
} RECTD;
_LGL_END