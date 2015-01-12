#pragma once
#include "Preprocess.h"

_LGL_BEGIN
interface IRenderable
{
public:
	virtual void Render() = 0;
protected:
	bool visible = true;
};
_LGL_END