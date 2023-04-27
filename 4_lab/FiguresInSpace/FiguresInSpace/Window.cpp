#include "pch.h"
#include "Window.h"

namespace
{
	// Угол обзора по вертикали
	constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;
	// Размер стороны куба
	constexpr double CUBE_SIZE = 1;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 10;
} // namespace

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_cube(CUBE_SIZE)
{
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Z_POSITIVE_Y_FACE, 20, 220, 0);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Z_NEGATIVE_Y_FACE, 20, 220, 0);

	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Z_FACE, 50, 150, 0);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Z_FACE, 50, 150, 0);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Y_POSITIVE_Z_FACE, 0, 50, 150);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Y_NEGATIVE_Z_FACE, 0, 50, 150);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Z_FACE, 0, 250, 0);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Z_FACE, 0, 250, 0);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Z_POSITIVE_Y_FACE, 200, 0, 150);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_Z_NEGATIVE_Y_FACE, 200, 0, 150);

	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Y_NEGATIVE_Z_FACE, 150, 170, 30);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_Y_POSITIVE_Z_FACE, 150, 170, 30);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 255, 255, 0);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 238, 130, 238);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 0, 250, 154);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 123, 104, 225);

	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 255, 0, 0);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 0, 255, 255);
	m_cube.SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 255, 215, 0);
	m_cube.SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 220, 20, 60);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	const auto proj = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&proj[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
}

void Window::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	const auto mat = glm::lookAt(glm::dvec3{ 2, 2, 2 }, glm::dvec3{ 0, 0, 0 }, glm::dvec3{ 0, 1, 0 });
	glLoadMatrixd(&mat[0][0]);

	m_cube.Draw();
}
