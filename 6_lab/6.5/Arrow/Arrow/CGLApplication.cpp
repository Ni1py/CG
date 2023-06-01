#include "CGLApplication.h"
#include "ShaderLoader.h"

CGLApplication::CGLApplication(char const* title, Size windowSize)
	: BaseApplication(title, windowSize.width, windowSize.height)
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

	glUseProgram(m_program);

	glBegin(GL_LINES);
	{
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(0.5f, 0.0f);
	}
	glEnd();

	glUseProgram(0);
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
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error("geometry shaders are not supported");
	}

	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "Shaders/arrowVertex.glsl");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "Shaders/arrowFragment.glsl");
	Shader geometryShader = loader.LoadShader(GL_GEOMETRY_SHADER, "Shaders/arrowGeometry.glsl");

	vertexShader.Compile();
	fragmentShader.Compile();
	geometryShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);
	m_program.AttachShader(geometryShader);

	m_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_LINES);
	m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_LINE_STRIP);
	m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 5);

	m_program.Link();
}
