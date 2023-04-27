#include "CoordinateAxes.h"

CoordinateAxes::CoordinateAxes()
{}

void CoordinateAxes::DrawCoordinateAxes() const
{
	DrawOX();
	DrawOY();
}

void CoordinateAxes::DrawOX()
{
	//рисование самой линии OX
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.1f, 0.0f);
	glVertex2f(1.1f, 0.0f);
	glEnd();

	//рисование штрихов
	for (float i = -1.0f; i < 1.1f; i += 0.1f)
	{
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(i, 0.02f);
		glVertex2f(i, -0.02f);
		glEnd();
	}

	//рисование стрелки
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(1.05f, 0.02f);
	glVertex2f(1.1f, 0.0f);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(1.05f, -0.02f);
	glVertex2f(1.1f, 0.0f);
	glEnd();
}

void CoordinateAxes::DrawOY()
{
	//рисование самой линии OY
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, -1.1f);
	glVertex2f(0.0f, 1.1f);
	glEnd();

	//рисование штрихов
	for (float i = -1.0f; i < 1.1f; i += 0.1f)
	{
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.02f, i);
		glVertex2f(-0.02f, i);
		glEnd();
	}

	//рисование стрелки
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.02f, 1.05f);
	glVertex2f(0.0f, 1.1f);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.02f, 1.05f);
	glVertex2f(0.0f, 1.1f);
	glEnd();
}