#pragma once
#include "LiongGLAPI.h"

_LGL_BEGIN
class _GL_ GLToolkit
{
public:
	GLToolkit();
	bool CreateGLWindow();
	void ResizeGLWindow(SIZE size);
	void DrawTestingImage();
	void SwapGLBuffers();
	void RemoveGLWindow();
	~GLToolkit();
private:
	static LRESULT CALLBACK WindowMessageProcesser(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HGLRC hRenderingContext= NULL;
	HDC hDeviceContext = NULL;
	HINSTANCE hInstance = NULL;
	HWND hWindow;
	UINT uTimer;
};
_LGL_END
