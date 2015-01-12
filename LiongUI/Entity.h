#pragma once
#include "Preprocess.h"
#include "LiongGL\Entrance.h"
#include "IClickable.h"

using namespace LiongStudio::GL;

_LUI_BEGIN
class _UI_ Entity : public IRenderable
{
public:
	void IRenderable::Render() override;
	void BindTexture(Texture *texture)
	{
		if (!texture)
			return;
		this->texture = texture;
	}
	virtual void SetPosition(POINTD position)
	{
		this->pos = position;
	}
	virtual void SetSize(SIZED size)
	{
		this->size = size;
	}
	virtual void SetAlpha(unsigned char alpha)
	{
		this->alpha = alpha;
	}
	virtual unsigned int GetTag()
	{
		return EntityType::IRenderable;
	}
protected:
	unsigned char alpha = 255;
	Texture *texture = nullptr;
	Renderer renderer;
	POINTD pos;
	SIZED size;
};
_LUI_END