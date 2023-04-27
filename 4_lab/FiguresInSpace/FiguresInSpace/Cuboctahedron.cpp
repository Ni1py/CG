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
		{ 11, 7, 10 }, // ���� ����� ��� ��������
		{ 1, 7, 11 },  // ��� ����� ��� ��������
		{ 7, 2, 6 },   // ��� ���� ��� ��������
		{ 2, 5, 6 },   // ���� ���� ��� ��������
		{ 1, 0, 2 },   // ��� ��� ������� ��������
		{ 0, 3, 2 },   // ���� ��� ������� ��������
		{ 0, 11, 9 },  // ��� ��� ������� ��������
		{ 0, 9, 4 },   // ���� ��� ������� ��������
		{ 4, 8, 5 },   // ���� ����� ������� ��������
		{ 3, 4, 5 },   // ��� ����� ������� ��������
		{ 9, 6, 8 },   // ���� ���� ��� ��������
		{ 10, 6, 9 },   // ��� ���� ��� ��������
		{ 11, 10, 9 }, // ����� ���� ���� ����
		{ 10, 7, 6 },  // ������ ���� ���� ����
		{ 0, 1, 11 },  // ����� ��� ���� ����
		{ 1, 2, 7 },   // ������ ��� ���� ����
		{ 4, 9, 8 },   // ����� ���� ������� ����
		{ 8, 6, 5 },   // ������ ���� ������� ����
		{ 0, 4, 3 },   // ����� ��� ������� ����
		{ 3, 5, 2 },   // ������ ��� ������� ����
	};

	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	// ��������� ������� ������� �������������-���� � ����� ������
	// �.�. ��������� ������� ��� ����� �������������� ��� ������ glScale
	glPushMatrix();
	// ������ ��������������� ������ ������
	glScalef(m_size * 0.5f, m_size * 0.5f, m_size * 0.5f);

	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < faceCount; ++face)
		{
			// ������������� ���� �����
			glColor4ubv(m_sideColors[face]);

			// ������ ��������������� �����, ���������� �� �������
			for (size_t i = 0; i < 3; ++i)
			{
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
	}
	glEnd();

	// ��������������� ������� ������������� ���� �� ����� ������
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
