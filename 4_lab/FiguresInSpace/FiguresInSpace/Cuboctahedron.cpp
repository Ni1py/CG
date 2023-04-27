#include "pch.h"
#include "Cuboctahedron.h"

Cuboctahedron::Cuboctahedron(float size)
	: m_size(size)
{
	SetSideColor(CuboctahedronSide::POSITIVE_Z_POSITIVE_Y_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_Z_NEGATIVE_Y_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Z_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Z_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::NEGATIVE_Y_POSITIVE_Z_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::NEGATIVE_Y_NEGATIVE_Z_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Z_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Z_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::NEGATIVE_Z_POSITIVE_Y_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::NEGATIVE_Z_NEGATIVE_Y_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::POSITIVE_Y_NEGATIVE_Z_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_Y_POSITIVE_Z_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_POSITIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_POSITIVE_Z_CORNER, 255, 255, 255);

	SetSideColor(CuboctahedronSide::NEGATIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_X_POSITIVE_Y_NEGATIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::NEGATIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 255, 255, 255);
	SetSideColor(CuboctahedronSide::POSITIVE_X_NEGATIVE_Y_NEGATIVE_Z_CORNER, 255, 255, 255);
}

void Cuboctahedron::Draw() const
{
	static constexpr float vertices[12][3] = {
		{ -1, -1, 0 }, // 0
		{ 0, -1, +1 }, // 1
		{ +1, -1, 0 }, // 2
		{ 0, -1, -1 }, // 3
		{ -1, 0, -1 }, // 4
		{ +1, 0, -1 }, // 5
		{ +1, +1, 0 }, // 6
		{ +1, 0, +1 }, // 7
		{ 0, +1, -1 }, // 8
		{ -1, +1, 0 }, // 9
		{ 0, +1, +1 }, // 10
		{ -1, 0, +1 }, // 11
	};

	static constexpr unsigned char faces[20][3] = {
		{ 11, 7, 10 }, // верх центр лиц квадрата
		{ 1, 7, 11 },  // низ центр лиц квадрата
		{ 7, 2, 6 },   // лев прав лиц квадрата
		{ 2, 5, 6 },   // прав прав лиц квадрата
		{ 1, 0, 2 },   // низ низ невидим квадрата
		{ 0, 3, 2 },   // верх низ невидим квадрата
		{ 0, 11, 9 },  // лев лев невидим квадрата
		{ 0, 9, 4 },   // прав лев невидим квадрата
		{ 4, 8, 5 },   // верх центр невидим квадрата
		{ 3, 4, 5 },   // низ центр невидим квадрата
		{ 9, 6, 8 },   // верх верх лиц квадрата
		{ 10, 6, 9 },   // низ верх лиц квадрата
		{ 11, 10, 9 }, // левый верх угол лица
		{ 10, 7, 6 },  // правый верх угол лица
		{ 0, 1, 11 },  // левый низ угол лица
		{ 1, 2, 7 },   // правый низ угол лица
		{ 4, 9, 8 },   // левый верх невидим угла
		{ 8, 6, 5 },   // правый верх невидим угла
		{ 0, 4, 3 },   // левый низ невидим угла
		{ 3, 5, 2 },   // правый низ невидим угла
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	// Сохраняем текущую матрицу моделирования-вида в стеке матриц
	// т.к. следующей строкой она будет модифицирована при помощи glScale
	glPushMatrix();
	// Задаем масштабирование вершин граней
	glScalef(m_size * 0.5f, m_size * 0.5f, m_size * 0.5f);

	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < faceCount; ++face)
		{
			// устанавливаем цвет грани
			glColor4ubv(m_sideColors[face]);

			// задаем четырехугольную грань, перечисляя ее вершины
			for (size_t i = 0; i < 3; ++i)
			{
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
	}
	glEnd();

	// Восстанавливаем матрицу моделирования вида из стека матриц
	glPopMatrix();
}

void Cuboctahedron::SetSideColor(CuboctahedronSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	int index = static_cast<int>(side);
	m_sideColors[index][0] = r;
	m_sideColors[index][1] = g;
	m_sideColors[index][2] = b;
	m_sideColors[index][3] = a;
}
