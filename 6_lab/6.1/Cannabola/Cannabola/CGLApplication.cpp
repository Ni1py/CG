#include "CGLApplication.h"
#include "ShaderLoader.h"

CGLApplication::CGLApplication(char const* title, Size windowSize)
	: BaseApplication(title, windowSize.width, windowSize.height),
	m_windowSize(windowSize)
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

	//поворот шейдера
	auto rotateVector = glm::vec3(0.f, 0.f, 90.f);
	GLint rotateUniform = glGetUniformLocation(m_program, "u_rotate");
	auto rotateMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotateVector.x), glm::vec3(1.f, 0.f, 0.f));
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotateVector.y), glm::vec3(0.f, 1.f, 0.f));
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotateVector.z), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(rotateUniform, 1, GL_FALSE, glm::value_ptr(rotateMatrix));

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
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "cannabola.fsh");

	vertexShader.Compile();
	fragmentShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	m_program.Link();
}
