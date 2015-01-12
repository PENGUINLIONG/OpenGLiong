#pragma once
#include <Windows.h>
#include <map>
#include "Preprocess.h"
#include "LiongGL\Entrance.h"
#include "IClickable.h"
#include "Entity.h"
#include "Character.h"
#include "Button.h"

using namespace LiongStudio::GL;

_LUI_BEGIN
class _UI_ Window
{
public:
	Window(SIZE size);
	bool Create();
	void Resize(SIZE size);
	void DrawTestImage();
	void Flush()
	{
		SwapBuffers(hDeviceContext);
	}
	void Remove();
	void Click(POINT point);
	void Render();
	unsigned int AppendEntity(Entity *Entity);
	Renderer &GetRenderer()
	{
		return renderer;
	}
	Entity *&GetEntity(unsigned int id)
	{
		return entitys[id];
	}
	~Window();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HGLRC hRenderingContext = NULL;
	HDC hDeviceContext = NULL;
	HINSTANCE hInstance = NULL;
	HWND hWindow;
	UINT uTimer;

	SIZE size;
	Renderer renderer;
	unsigned int entityID = 0;
	map<unsigned int, Entity *> entitys;
};
_LUI_END