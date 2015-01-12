#include "Button.h"
#include <iostream>
using namespace std;
#pragma warning( disable: 4244 )

_LUI_BEGIN
Button::Button(Renderer &renderer)
{
	this->renderer = renderer;
	available = true;
}

bool Button::CheckClick(SIZE window, POINT point)
{
	if (!available)
		return false;

	int x0 = window.cx * (pos.x + 50.0f) / 100, y0 = window.cy * (50.0f - pos.y) / 100,
		x1 = window.cx * (pos.x + size.width + 50.0f) / 100, y1 = window.cy * (50.0f - pos.y + size.height) / 100;

	if (x0 <= point.x && point.x <= x1 && y0 <= point.y && point.y <= y1)
	{
		if (texture->PixelFormat == GL_BGR_EXT || texture->PixelFormat == GL_RGB8 || texture->PixelFormat == GL_RGB16)
			return true;
		else if (texture->PixelFormat == GL_BGRA_EXT || texture->PixelFormat == GL_RGBA8 || texture->PixelFormat == GL_RGBA16)
		{
			int pixelLength = texture->GetPixelLength();
			if (pixelLength < 5)
			{
				if (*(unsigned char *)(texture->Data + ((point.x - x0) + (point.y - y0) * texture->Size.cx) * pixelLength + 3)) // Calculate the offset to the pixel.
					return true;
			}
			else
			{
				if (*(unsigned short *)(texture->Data + ((point.x - x0) + (point.y - y0) * texture->Size.cx) * pixelLength + 6)) // Calculate the offset to the pixel.
					return true;
			}
		}
	}
	return false;
}

void Button::ClickEventHandler(POINT point)
{
	cout << "Button clicked! At (" << point.x << ", " << point.y << ")." << endl;
}

Button::~Button()
{
}
_LUI_END