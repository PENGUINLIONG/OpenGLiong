#include "Renderer.h"

_LGL_BEGIN
Renderer::Renderer()
{
}

#define 左上 0.0f, 1.0f
#define 左下 0.0f, 0.0f
#define 右上 1.0f, 1.0f
#define 右下 1.0f, 0.0f

void Renderer::DrawRectangle(GLuint textureID, RECTD rect)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(左上);
		glVertex2d(rect.left, rect.top);
		glTexCoord2f(左下);
		glVertex2d(rect.left, rect.bottom);
		glTexCoord2f(右下);
		glVertex2d(rect.right, rect.bottom);
		glTexCoord2f(右上);
		glVertex2d(rect.right, rect.top);
	}
	glEnd();
}

void Renderer::DrawRectangleUpsideDown(GLuint textureID, RECTD rect)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(右下);
		glVertex2d(rect.left, rect.top);
		glTexCoord2f(右上);
		glVertex2d(rect.left, rect.bottom);
		glTexCoord2f(左上);
		glVertex2d(rect.right, rect.bottom);
		glTexCoord2f(左下);
		glVertex2d(rect.right, rect.top);
	}
	glEnd();
}

void Renderer::DrawBackGroundImage(GLuint textureID)
{
	double ratio = (double)window.cx / (double)window.cy;
	DrawRectangle(textureID, { ratio * -50.0f, 50, ratio * 50.0f, -50.0f });
}

void Renderer::DrawWithoutTexture(RECTD rect)
{
	glColor3ub(229, 229, 229);
	glBegin(GL_QUADS);
	{
		glVertex2d(rect.left, rect.top);
		glVertex2d(rect.left, rect.bottom);
		glVertex2d(rect.right, rect.bottom);
		glVertex2d(rect.right, rect.top);
	}
	glEnd();

	glColor3ub(153, 153, 153);
	glBegin(GL_LINE_STRIP);
	{
		glVertex2d(rect.left, rect.top);
		glVertex2d(rect.left, rect.bottom);
		glVertex2d(rect.right, rect.bottom);
		glVertex2d(rect.right, rect.top);
		glVertex2d(rect.left, rect.top);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex2d(rect.left, rect.top);
		glVertex2d(rect.right, rect.bottom);
		glVertex2d(rect.right, rect.top);
		glVertex2d(rect.left, rect.bottom);
	}
	glEnd();
}

void Renderer::Resize(SIZE size)
{
	window.cx = size.cx;
	window.cy = size.cy;
}

Renderer::~Renderer()
{
}
_LGL_END
