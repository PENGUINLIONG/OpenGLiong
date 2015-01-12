#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "IClickable.h"
#include "LiongGL\Entrance.h"

using namespace LiongStudio::GL;

_LUI_BEGIN
class _UI_ Button : public Entity, public IClickable
{
public:
	Button(Renderer &renderer);
	bool IClickable::CheckClick(SIZE window, POINT point) override final;
	void IClickable::ClickEventHandler(POINT point) override final;
	unsigned int GetTag() override final
	{
		return EntityType::IClickable | EntityType::IRenderable;
	}
	~Button();
private:
	bool available = false;
};
_LUI_END