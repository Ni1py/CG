#include "CGLApplication.h"
#include "ShaderLoader.h"

CGLApplication::CGLApplication(char const* title)
	: BaseApplication(title, 800, 600)
{
}

void CGLApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1, 1, 1, 1);

	glLoadIdentity();
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	InitShaders();
}

void CGLApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glScalef(0.6f, 0.6f, 1);
	glTranslatef(0, -1, 0);
	glUseProgram(m_program);

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	{
		for (double x = 0; x <= 2 * M_PI; x += M_PI / 1000)
		{
			glVertex2d(x, 0);
		}
	}
	glEnd();

	glUseProgram(0);
	glPopMatrix();
}

void CGLApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
}

void CGLApplication::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "cannabola.vsh");

	vertexShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);

	m_program.Link();
}
