#include "Character.h"

_LSPRITE_BEGIN
Character::Character()
{
}

void Character::BindTexture(uint textureIndex)
{
	this->textureIndex = textureIndex;
}

void Character::ResetGeology(Position position, Size size)
{
	this->position = position_Original = position;
	this->size = size;
	fxCounter = 0;
}

void Character::SwitchDisplayMode(CharacterDisplayMode displayMode)
{
	this->displayMode = displayMode;
	if (displayMode == CharacterDisplayMode::Hidden)
		this->available = false;
	else
		this->available = true;
}

void Character::SwitchFX(CharacterFX fx)
{
	this->fx = fx;
	fxCounter = 0;
	position = position_Original;
}

void Character::SetAlpha(unsigned char alpha)
{
	this->alpha = alpha;
}

bool Character::isAvailable()
{
	return available;
}

void Character::Render()
{
	if (!available)
		return;
	glColor4ub(255, 255, 255, alpha);
	if (displayMode == CharacterDisplayMode::Normal)
		Renderer::DrawRectangle(textureIndex, { position.X - 16.0f, 9.0f - position.Y, position.X + size.Width - 16.0f, 9.0f - position.Y - size.Height });
	else
		Renderer::DrawRectangleUpsideDown(textureIndex, { position.X - 16.0f, 9.0f - position.Y, position.X + size.Width - 16.0f, 9.0f - position.Y - size.Height });
	if (fx != CharacterFX::Normal)
		ProcessFX();
	glColor4ub(255, 255, 255, 255);
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
					position = position_Original;
				fxCounter++;
				return;
			}
			else
				fxCounter += 20;

			position.X += sin(fxCounter) / 10.0f;
			return;
		}
		case CharacterFX::Flowing:
		{
			if (fxCounter >= 250)
			{
				if (fxCounter == 250)
				{
					position = position_Original;
					fxCounter = 0;
				}
				return;
			}
			else
				fxCounter++;

			position.X += sin(fxCounter / 20.0f) / 30.0f;
			position.Y += cos(fxCounter / 10.0f) / 15.0f;
			return;
		}
		case CharacterFX::Abnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					position = { position.X - 0.5f, position.Y };
					fxCounter++;
					return;
				}
				case 15:
				{
					position = { position.X + 0.25f, position.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 30:
				{
					position = { position.X + 0.25f, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 45:
				{
					position = { position.X - 0.5f, position.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 60:
				{
					position = { position.X + 0.75, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 75:
				{
					position = { position.X + 0.5f, position.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 90:
				{
					position = position_Original;
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
					position = { position.X - 0.5f, position.Y };
					fxCounter++;
					return;
				}
				case 5:
				{
					position = { position.X + 0.25f, position.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 10:
				{
					position = { position.X + 0.25f, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 15:
				{
					position = { position.X - 0.5f, position.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 20:
				{
					position = { position.X + 0.75, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 25:
				{
					position = { position.X + 0.5f, position.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 30:
				{
					position = position_Original;
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
					position = { position.X - 0.5f, position.Y };
					fxCounter++;
					return;
				}
				case 2:
				{
					position = { position.X + 0.25f, position.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 4:
				{
					position = { position.X + 0.25f, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 6:
				{
					position = { position.X - 0.5f, position.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 8:
				{
					position = { position.X + 0.75, position.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 10:
				{
					position = { position.X + 0.5f, position.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 12:
				{
					position = position_Original;
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
_LSPRITE_END
