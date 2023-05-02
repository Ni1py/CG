#include "pch.h"
#include "Window.h"

namespace
{
	// Размер стороны куба
	constexpr double CUBE_SIZE = 1;

	// Ортонормируем матрицу 4*4 (это должна быть аффинная матрица)
	glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
	{
		// Извлекаем подматрицу 3*3 из матрицы m и ортонормируем её
		const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
		// Заменяем 3 столбца исходной матрицы
		return {
			glm::dvec4{ normalizedMatrix[0], 0.0 },
			glm::dvec4{ normalizedMatrix[1], 0.0 },
			glm::dvec4{ normalizedMatrix[2], 0.0 },
			m[3]
		};
	}
} // namespace

void Window::OnMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}
}

// Вращаем камеру вокруг начала координат
void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	// Извлекаем из 1 и 2 строки матрицы камеры направления осей вращения,
	// совпадающих с экранными осями X и Y.
	// Строго говоря, для этого надо извлекать столбцы их обратной матрицы камеры, но так как
	// матрица камеры ортонормированная, достаточно транспонировать её подматрицу 3*3
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
}

void Window::OnMouseMove(double x, double y)
{
	const glm::dvec2 mousePos{ x, y };
	if (m_leftButtonPressed)
	{
		const auto windowSize = GetFramebufferSize();

		const auto mouseDelta = mousePos - m_mousePos;
		const double xAngle = mouseDelta.y * M_PI / windowSize.y;
		const double yAngle = mouseDelta.x * M_PI / windowSize.x;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_cube(CUBE_SIZE)
{
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Z_POSITIVE_Y_FACE, 20, 220, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Z_NEGATIVE_Y_FACE, 20, 220, 0, 100);

	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Z_FACE, 50, 150, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Z_FACE, 50, 150, 0, 100);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Y_POSITIVE_Z_FACE, 0, 50, 150, 100);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Y_NEGATIVE_Z_FACE, 0, 50, 150, 100);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Z_FACE, 0, 250, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Z_FACE, 0, 250, 0, 100);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Z_POSITIVE_Y_FACE, 200, 0, 150, 100);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Z_NEGATIVE_Y_FACE, 200, 0, 150, 100);

	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Y_NEGATIVE_Z_FACE, 150, 170, 30, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Y_POSITIVE_Z_FACE, 150, 170, 30, 100);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 255, 255, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 238, 130, 238, 100);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 0, 250, 154, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 123, 104, 225, 100);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 255, 0, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 0, 255, 255, 100);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 255, 215, 0, 100);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 220, 20, 60, 100);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	// Считаем, что высота видимой области равна FRUSTUM_SIZE
	// (на расстоянии до ближней плоскости отсечения)
	double frustumHeight = FRUSTUM_SIZE;
	// Ширина видимой области рассчитывается согласно соотношению сторон окна
	// (шире окно - шире область видимости и наоборот)
	double frustumWidth = frustumHeight * aspect;

	// Если ширина видимой области получилась меньше, чем FRUSTUM_SIZE,
	// то корректируем размеры видимой области
	if (frustumWidth < FRUSTUM_SIZE && (aspect != 0))
	{
		frustumWidth = FRUSTUM_SIZE;
		frustumHeight = frustumWidth / aspect;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-frustumWidth * 0.5, frustumWidth * 0.5, // left, right
		-frustumHeight * 0.5, frustumHeight * 0.5, // top, bottom
		FRUSTUM_SIZE * 0.5, FRUSTUM_SIZE * 20 // znear, zfar
	);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	//включаем режим смешивания цветов
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::Draw(int width, int height)
{
	//настраиваем на то, чтобы отбрасывались грани, кот рисуются против часовой
	glFrontFace(GL_CW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();

	glRotatef(90, 1, 0, 0);

	glPushMatrix();
	m_cube.Draw();
	glPopMatrix();

	//настраиваем на то, чтобы отбрасывались грани, кот рисуются по часовой
	glFrontFace(GL_CCW);
	m_cube.Draw();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}
