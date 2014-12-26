#pragma once
#include <Windows.h>

#ifdef LiongUI_Export
#define _UI_ __declspec(dllexport)
#else
#define _UI_ __declspec(dllimport)
#endif

typedef int code;

#define _LUI_BEGIN namespace LiongStudio { namespace Sound {
#define _LUI_END } }