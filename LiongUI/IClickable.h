#pragma once
#include "LiongUIAPI.h"

_LUI_BEGIN
__interface IClickable
{
	bool IsPointOn(POINT point);
	void OnClick();
};
_LUI_END