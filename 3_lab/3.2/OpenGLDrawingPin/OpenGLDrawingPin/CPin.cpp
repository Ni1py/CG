#include "CPin.h"

CPin::CPin(PointGL translate, PointGL scale, ColorRGB hatColor)
	:m_translate(translate), m_scale(scale), m_hatColor(hatColor)
{}

void CPin::DrawPin() const
{
	glTranslatef(m_translate.x, m_translate.y, m_translate.z);
	glScalef(m_scale.x, m_scale.y, m_scale.z);

	//Рисуем левую руку
	glPushMatrix();
	glTranslatef(-0.5, 0.4, 0.0);
	glRotatef(100, 0.0, 0.0, 1.0);
	DrawHand();
	glPopMatrix();

	//Рисуем правую руку
	glPushMatrix();
	glTranslatef(0.5, -0.3, 0.0);
	glRotatef(-60, 0.0, 0.0, 1.0);
	DrawHand();
	glPopMatrix();

	//Рисуем левую ногу
	glPushMatrix();
	glTranslatef(-0.3, -0.3, 0.0);
	glRotatef(-70, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawLeg();
	glPopMatrix();

	//Рисуем тело
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.5f, 0.5f);
	glPopMatrix();

	//Рисуем живот
	glPushMatrix();
	glRotatef(200, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.0f, 0.0f, 0.47f, 0.47f, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.31, 0.0);
	glRotatef(-25, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.35f, 0.5f, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.32, 0.0);
	glRotatef(-25, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.0f, 0.0f, 0.314f, 0.23f, 1.0);
	glPopMatrix();

	//Рисуем клюв
	glPushMatrix();
	glTranslatef(0.05, 0.18, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.3, 0.3, 1);
	DrawBeak();
	glPopMatrix();

	//Рисуем глаза
	glPushMatrix();
	glTranslatef(0.01, 0.35, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.8, 0.8, 1);
	DrawEye();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, 0.3, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.8, 0.8, 1);
	DrawEye();
	glPopMatrix();

	//Рисуем шляпу
	glPushMatrix();
	glTranslatef(0.15, 0.51, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawHat(m_hatColor);
	glPopMatrix();

	//Рисуем очки
	glPushMatrix();
	glTranslatef(0.13, 0.45, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.3, 0.3, 1);
	DrawGlasses();
	glPopMatrix();

	//Рисуем правую ногу
	glPushMatrix();
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(-50, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawLeg();
	glPopMatrix();
}

void CPin::DrawEllipse(float xCenter, float yCenter, float rx, float ry, float countPi, int points)
{
	const float step = static_cast<float>(M_PI * countPi / points);

	// Эллипс представлет в виде "веера" из треугольников
	glBegin(GL_TRIANGLE_FAN);
	// Начальная точка веера располагается в центре эллипса
	glVertex2d(xCenter, yCenter);
	// Остальные точки - равномерно по его границе
	for (float angle = 0; angle <= M_PI * countPi; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - M_PI * countPi)) < 1e-5) ? 0 : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void CPin::DrawHand()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.4f, 0.4f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.2f, 0.0, 0.45f, 0.25f);
}

void CPin::DrawLeg() 
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, -0.4f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.5f, -0.7f);
	glVertex2f(-0.5f, -0.3f);
	glEnd();
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, -0.4f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.5f, -0.7f);
	glVertex2f(-0.5f, -0.3f);
	glEnd();
}

void CPin::DrawBeak() {
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse(-0.6f, 0.0f, 0.2f, 0.2f);

	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse(0.6f, 0.0f, 0.2f, 0.2f);

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.4f, 0.3f, 0.2f, 1.0f);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.6f, 0.2f);
	glVertex2f(-0.6f, -0.2f);
	glVertex2f(-0.3f, -0.4f);
	glVertex2f(0.3f, -0.4f);
	glVertex2f(0.6f, -0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.05f, 0.4f);
	glVertex2f(-0.05f, 0.4f);
	glEnd();
}

void CPin::DrawEye()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.0f, 0.0f, 0.1, 0.14);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.03, 0.03);
}

void CPin::DrawHat(ColorRGB hatColor)
{
	//glColor3f(0.7f, 0.4f, 0.0f);
	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(-0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(-0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(0.0f, 0.3f, 0.4f, 0.3f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.4f, 0.31f);
	glVertex2f(0.4f, 0.31f);
	glVertex2f(0.6f, -0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(-0.8f, -0.1f);
	glVertex2f(-0.5f, -0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.8f, -0.1f);
	glVertex2f(0.5f, -0.1f);
	glEnd();
	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(-0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(-0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse(0.0f, 0.3f, 0.4f, 0.3f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.4f, 0.31f);
	glVertex2f(0.4f, 0.31f);
	glVertex2f(0.6f, -0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(-0.8f, -0.1f);
	glVertex2f(-0.5f, -0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.8f, -0.1f);
	glVertex2f(0.5f, -0.1f);
	glEnd();
}

void CPin::DrawGlasses()
{
	glColor3f(0.5f, 0.2f, 0.0f);

	DrawEllipse(-0.2f, 0.0f, 0.3f, 0.3f);

	DrawEllipse(0.2f, 0.0f, 0.3f, 0.3f);

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(-0.2f, 0.3f);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(0.2f, 0.3f);
	glVertex2f(0.8f, 0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	glColor3f(0.5f, 1.0f, 1.0f);

	DrawEllipse(-0.2f, 0.0f, 0.15f, 0.15f);

	glBegin(GL_QUADS);
	glVertex2f(-0.2f, 0.15f);
	glVertex2f(-0.6f, 0.15f);
	glVertex2f(-0.6f, -0.15f);
	glVertex2f(-0.2f, -0.15f);
	glEnd();

	DrawEllipse(0.2f, 0.0f, 0.15f, 0.15f);

	glBegin(GL_QUADS);
	glVertex2f(0.2f, 0.15f);
	glVertex2f(0.6f, 0.15f);
	glVertex2f(0.6f, -0.15f);
	glVertex2f(0.2f, -0.15f);
	glEnd();
}
