#include "Parabola.h"

Parabola::Parabola(PointGL translate)
	:m_translate(translate)
{}

void Parabola::DrawParabola() const
{
	glTranslatef(m_translate.x, m_translate.y, m_translate.z);

	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.7f, 0.0f, 0.5f);
	for (float i = 0.0f; i < 1.1f; i += 0.1f)
	{
		glVertex2f(i, i * i);
	}
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.7f, 0.0f, 0.5f);
	for (float i = 0.0f; i > -1.1f; i -= 0.1f)
	{
		glVertex2f(i, i * i);
	}
	glEnd();
}