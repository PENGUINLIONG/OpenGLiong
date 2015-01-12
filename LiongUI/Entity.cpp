#include "Entity.h"

_LUI_BEGIN
void Entity::Render()
{
	if (!visible)
		return;
	if (!texture)
	{
		renderer.DrawWithoutTexture({ pos.x, pos.y, pos.x + size.width, pos.y - size.height });
		return;
	}
	glColor4ub(255, 255, 255, alpha);
	renderer.DrawRectangle(texture->Index, { pos.x, pos.y, pos.x + size.width, pos.y - size.height });
}
_LUI_END