#pragma once
#include "LiongGL\LiongGLAPI.h"
#include "LiongUIAPI.h"
#include "IClickable.h"

_LUI_BEGIN
class Button : public IClickable
{
public:
	Button();
	bool IsPointOn(unsigned int vPoint);
	void OnClick();
	~Button();
private:
	bool available;
	unsigned int vUpperLeft = 0;
	unsigned int vLowerRight = 0;
};
_LUI_END