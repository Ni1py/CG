#include "CGLApplication.h"
#include "ShaderLoader.h"

DWORD g_lastTick = GetTickCount();

CGLApplication::CGLApplication(char const* title, Size windowSize)
	: BaseApplication(title, windowSize.width, windowSize.height),
	m_windowSize(windowSize),
	m_surface(20, 10, -1, 1, -0.5, 0.5)
{
}

void CGLApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	//�������� ������ � ����� �������
	glDepthMask(GL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1, 1, 1, 1);

	glLoadIdentity();
	gluLookAt(
		2.5, 2.5, -1,
		0, 0, 0,
		1, 1, 0);

	InitShaders();
}

void CGLApplication::OnDisplay()
{
	DWORD currentTick = (DWORD)GetTickCount64();
	float time = (currentTick - g_lastTick) / 1000.0f;
	g_lastTick = currentTick;

	static float workTime = 0;
	workTime += time;
	if (workTime >= 3)
	{
		workTime -= 4;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	//glScalef(0.6f, 0.6f, 1);
	//glTranslatef(-1.5, -2, -0.5);
	glUseProgram(m_program);

	GLint timeUniform = glGetUniformLocation(m_program, "u_time");
	glUniform1f(timeUniform, workTime);

	glColor3f(0, 0, 0);
	m_surface.Draw();

	glUseProgram(0);
	glPopMatrix();

	PostRedisplay();
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
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/TransformationVertex.glsl");
	//Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "cannabola.fsh");

	vertexShader.Compile();
	//fragmentShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	//m_program.AttachShader(fragmentShader);

	m_program.Link();
}
