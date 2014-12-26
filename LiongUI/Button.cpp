#include "Button.h"

_LUI_BEGIN
Button::Button()
{
}

bool Button::IsPointOn(unsigned int vPoint)
{
	if (vPoint >= vUpperLeft && vPoint <= vLowerRight)
		return true;
	else
		return false;
}

void Button::OnClick()
{

}

Button::~Button()
{
}
_LUI_END