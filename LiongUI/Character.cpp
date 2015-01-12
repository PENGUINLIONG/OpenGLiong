#include "Character.h"

_LUI_BEGIN
Character::Character(Renderer &renderer)
{
	this->renderer = renderer;
	visible = true;
}

void Character::Render()
{
	if (!visible)
		return;
	if (!texture)
	{
		renderer.DrawWithoutTexture({ pos.x, pos.y, pos.x + size.width, pos.y - size.height });
		return;
	}
	glColor4ub(255, 255, 255, alpha);
	if (this->displayMode == CharacterDisplayMode::Normal)
		renderer.DrawRectangle(texture->Index, { pos.x, pos.y, pos.x + size.width, pos.y - size.height });
	else
		renderer.DrawRectangleUpsideDown(texture->Index, { pos.x, pos.y, pos.x + size.width, pos.y + size.height });
	if (fx != CharacterFX::Normal)
		ProcessFX();
}

void Character::SetPosition(POINTD position)
{
	Entity::SetPosition(position);
	fxCounter = 0;
	pos_Original = position;
}
void Character::SetSize(SIZED size)
{
	Entity::SetSize(size);
	fxCounter = 0;
	pos = pos_Original;
}
void Character::SwitchDisplayMode(CharacterDisplayMode displayMode)
{
	if (displayMode == CharacterDisplayMode::Inherit)
		return;
	if (displayMode == CharacterDisplayMode::Hidden)
		visible = false;
	else
		visible = true;
	this->displayMode = displayMode;
}
void Character::SwitchFX(CharacterFX fx)
{
	if (fx == CharacterFX::Inherit)
		return;
	this->fx = fx;
	fxCounter = 0;
	pos = pos_Original;
}

void Character::ProcessFX()
{
	switch (fx)
	{
		case CharacterFX::Shaky:
		{
			if (fxCounter >= 360)
			{
				if (fxCounter >= 600)
				{
					fxCounter = 0;
					return;
				}
				if (fxCounter == 360)
					pos = pos_Original;
				fxCounter++;
				return;
			}
			else
				fxCounter += 20;

			pos.x += sin((double)fxCounter) / 10.0f;
			return;
		}
		case CharacterFX::Flowing:
		{
			if (fxCounter >= 250)
			{
				if (fxCounter == 250)
				{
					pos = pos_Original;
					fxCounter = 0;
				}
				return;
			}
			else
				fxCounter++;

			pos.x += sin(fxCounter / 20.0f) / 30.0f;
			size.width += sin(fxCounter / 20.0f) / 30.0f;
			pos.y += cos(fxCounter / 10.0f) / 15.0f;
			size.height += cos(fxCounter / 10.0f) / 15.0f;
			return;
		}
		case CharacterFX::Abnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.x - 0.5f, pos.y };
					fxCounter++;
					return;
				}
				case 15:
				{
					pos = { pos.x + 0.25f, pos.y - 0.5f };
					fxCounter++;
					return;
				}
				case 30:
				{
					pos = { pos.x + 0.25f, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 45:
				{
					pos = { pos.x - 0.5f, pos.y + 0.5f };
					fxCounter++;
					return;
				}
				case 60:
				{
					pos = { pos.x + 0.75, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 75:
				{
					pos = { pos.x + 0.5f, pos.y - 0.25f };
					fxCounter++;
					return;
				}
				case 90:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
		case CharacterFX::ExAbnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.x - 0.5f, pos.y };
					fxCounter++;
					return;
				}
				case 5:
				{
					pos = { pos.x + 0.25f, pos.y - 0.5f };
					fxCounter++;
					return;
				}
				case 10:
				{
					pos = { pos.x + 0.25f, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 15:
				{
					pos = { pos.x - 0.5f, pos.y + 0.5f };
					fxCounter++;
					return;
				}
				case 20:
				{
					pos = { pos.x + 0.75, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 25:
				{
					pos = { pos.x + 0.5f, pos.y - 0.25f };
					fxCounter++;
					return;
				}
				case 30:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
		case CharacterFX::ExExAbnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.x - 0.5f, pos.y };
					fxCounter++;
					return;
				}
				case 2:
				{
					pos = { pos.x + 0.25f, pos.y - 0.5f };
					fxCounter++;
					return;
				}
				case 4:
				{
					pos = { pos.x + 0.25f, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 6:
				{
					pos = { pos.x - 0.5f, pos.y + 0.5f };
					fxCounter++;
					return;
				}
				case 8:
				{
					pos = { pos.x + 0.75, pos.y + 0.25f };
					fxCounter++;
					return;
				}
				case 10:
				{
					pos = { pos.x + 0.5f, pos.y - 0.25f };
					fxCounter++;
					return;
				}
				case 12:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
	}
}

Character::~Character()
{
}
_LUI_END