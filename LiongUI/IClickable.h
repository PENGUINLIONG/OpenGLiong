#pragma once
#include "Preprocess.h"
#include "LiongGL\Entrance.h"

using namespace LiongStudio::GL;

_LUI_BEGIN
interface IClickable
{	
public:
	virtual bool CheckClick(SIZE window, POINT point) = 0;
	virtual void ClickEventHandler(POINT point) = 0;
};
_LUI_END