#include "Renderer.h"

_LGL_BEGIN
void Renderer::DrawRectangle(uint textureID, Rectangle rect)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(rect.Left, rect.Top);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(rect.Left, rect.Bottom);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(rect.Right, rect.Bottom);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(rect.Right, rect.Top);
	}
	glEnd();
}

void Renderer::DrawRectangleUpsideDown(uint textureID, Rectangle rect)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(rect.Left, rect.Top);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(rect.Left, rect.Bottom);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(rect.Right, rect.Bottom);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(rect.Right, rect.Top);
	}
	glEnd();
}

void Renderer::DrawBackGroundImage(uint textureID)
{
	DrawRectangle(textureID, { -16.0f, 9.0f, 16.0f, -9.0f });
}
_LGL_END
