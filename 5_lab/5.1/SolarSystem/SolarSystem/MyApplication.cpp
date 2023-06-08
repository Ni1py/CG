#include "MyApplication.h"

// Расстояние до ближней плоскости отсечения отображаемого объема
const double CMyApplication::ZNEAR = 0.1;
// Расстояние до дальей плоскости отсечения отображаемого объема
const double CMyApplication::ZFAR = 200;
// Угол обзора по вертикали
const double CMyApplication::FIELD_OF_VIEW = 70;

CMyApplication::CMyApplication(const char* title, int width, int height)
	: CGLApplication(title, width, height)
	, m_sun(L"assets/8k_sun.jpg")
	, m_earth(L"assets/earth.png")
	, m_moon(L"assets/8k_moon.jpg")
	, m_rotationController(width, height)
	, m_light(CVector3f(0, 10, 0))
	, m_skyBox(
		  L"assets/Galaxy_LT.png",
		  L"assets/Galaxy_RT.png",
		  L"assets/Galaxy_DN.png",
		  L"assets/Galaxy_UP.png",
		  L"assets/Galaxy_BK.png",
		  L"assets/Galaxy_FT.png")
	, m_polygonMode(GL_FILL)
{
	m_light.SetDiffuseIntensity(1, 1, 1);
	m_light.SetSpecularIntensity(1, 1, 1);

	m_sun.SetRotationSpeed(20);
	//m_sun.SetInclinationAngle(1);

	m_earth.SetRotationSpeed(50);
	m_earth.SetInclinationAngle(23.43);

	m_moon.SetRotationSpeed(10);
	//m_moon.SetInclinationAngle(1);
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	gluLookAt(0, 2, 1, 0, 0, 0, 0, 0, 1);
}

void CMyApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Включаем режим наложения текстуры
	glEnable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);

	DrawSkyBox();
	DrawSun();

	glPushMatrix();
	for (int angle = 0; angle < 360; angle += 20)
	{
		float angleInRadians = (float)(angle * M_PI / 180.0f);
		float x = cosf(angleInRadians);
		float z = sinf(angleInRadians);
		glTranslatef(x, 0, z);
	}
	DrawEarth();
	glPopMatrix();
	glPushMatrix();
	for (int angle = 0; angle < 360; angle += 20)
	{
		float angleInRadians = (float)(angle * M_PI / 180.0f);
		float x = cosf(angleInRadians);
		float z = sinf(angleInRadians);
		glTranslatef(x, 0, z);
	}
	DrawMoon();
	glPopMatrix();

	PostRedisplay();
	Sleep(10);
}

void CMyApplication::DrawSun() const
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	m_light.SetLight(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glPushMatrix();
		glScalef(0.6, 0.6, 0.6);
		m_sun.Draw();
	glPopMatrix();
}

void CMyApplication::DrawEarth() const
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	m_light.SetLight(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glPushMatrix();
		glTranslatef(1.8, 0, 0);
		glScalef(0.2, 0.2, 0.2);
		m_earth.Draw();
	glPopMatrix();
}

void CMyApplication::DrawMoon() const
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	m_light.SetLight(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glPushMatrix();
		glTranslatef(1.4, 0, 0);
		glScalef(0.09, 0.09, 0.09);
		m_moon.Draw();
	glPopMatrix();
}

void CMyApplication::DrawSkyBox() const
{
	glDisable(GL_LIGHTING);
	// Отключим режим отбраковки граней, т.к.
	// мы находимся внутри куба и видим его нелицевую сторону
	glDisable(GL_CULL_FACE);
	m_skyBox.Draw();
}

void CMyApplication::OnIdle()
{
	m_animationController.Tick();
	m_sun.Animate(static_cast<float>(m_animationController.GetTimeDelta() * 0.001));
	m_earth.Animate(static_cast<float>(m_animationController.GetTimeDelta() * 0.001));
	m_moon.Animate(static_cast<float>(m_animationController.GetTimeDelta() * 0.001));
	PostRedisplay();
	Sleep(10);
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	m_rotationController.ResizeWindow(width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnMouse(int button, int state, int x, int y)
{
	// Событие от левой кнопки мыши
	m_rotationController.OnMouse(button, state, x, y);
}

void CMyApplication::OnMotion(int x, int y)
{
	// Если нажата левая кнопка мыши
	if (m_rotationController.LeftButtonIsPressed())
	{
		m_rotationController.OnMotion(x, y);

		// Инициируем перерисовку окна
		PostRedisplay();
	}
}

void CMyApplication::OnKeyboard(unsigned char key, int /*x*/, int /*y*/)
{
	if (key == ' ')
	{
		if (m_polygonMode == GL_FILL)
		{
			m_polygonMode = GL_LINE;
		}
		else if (m_polygonMode == GL_LINE)
		{
			m_polygonMode = GL_POINT;
		}
		else // polygon mode == GL_POINT
		{
			m_polygonMode = GL_FILL;
		}
		PostRedisplay();
	}
}