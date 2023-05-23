#include "pch.h"
#include "Cuboctahedron.h"

Cuboctahedron::Cuboctahedron(float size)
	: m_size(size)
{
	SetSideColor(CuboctahedronSide::FRONT_SQUARE_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::REAR_SQUARE_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::RIGHT_SQUARE_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LEFT_SQUARE_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::UPPER_SQUARE_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LOWER_SQUARE_FACE, 255, 255, 255);

	SetSideColor(CuboctahedronSide::RIGHT_UPPER_FRONT_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LEFT_UPPER_FRONT_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LEFT_LOWER_FRONT_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::RIGHT_LOWER_FRONT_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::RIGHT_UPPER_REAR_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LEFT_UPPER_REAR_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::LEFT_LOWER_REAR_TRIANGULAR_FACE, 255, 255, 255);
	SetSideColor(CuboctahedronSide::RIGHT_LOWER_REAR_TRIANGULAR_FACE, 255, 255, 255);
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

	static constexpr unsigned char triangularFaces[8][3] = {
		{ 11, 10, 9 }, // ����� ���� ���� ����
		{ 10, 7, 6 },  // ������ ���� ���� ����
		{ 0, 1, 11 },  // ����� ��� ���� ����
		{ 1, 2, 7 },   // ������ ��� ���� ����
		{ 4, 9, 8 },   // ����� ���� ������� ����
		{ 8, 6, 5 },   // ������ ���� ������� ����
		{ 0, 4, 3 },   // ����� ��� ������� ����
		{ 3, 5, 2 },   // ������ ��� ������� ����
	};

	static constexpr unsigned char squareFaces[6][4] = {
		{11, 1, 7, 10}, //�������
		{4, 8, 5, 3}, //������
		{7, 2, 5, 6}, //������
		{0, 11, 9, 4}, //�����
		{1, 0, 3, 2}, //������
		{10, 6, 8, 9}, //�������
	};

	static size_t const triangularFaceCount = sizeof(triangularFaces) / sizeof(*triangularFaces);
	static size_t const squareFaceCount = sizeof(squareFaces) / sizeof(*squareFaces);

	// ��������� ������� ������� �������������-���� � ����� ������
	// �.�. ��������� ������� ��� ����� �������������� ��� ������ glScale
	glPushMatrix();
	// ������ ��������������� ������ ������
	glScalef(m_size * 0.5f, m_size * 0.5f, m_size * 0.5f);

	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < triangularFaceCount; ++face)
		{
			// ������������� ���� �����
			glColor4ubv(m_sideColors[face + 6]);

			// ������ ����������� �����, ���������� �� �������
			for (size_t i = 0; i < 3; ++i)
			{
				size_t vertexIndex = triangularFaces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < squareFaceCount; ++face)
		{
			// ������������� ���� �����
			glColor4ubv(m_sideColors[face]);

			// ������ ��������������� �����, ���������� �� �������
			for (size_t i = 0; i < 4; ++i)
			{
				size_t vertexIndex = squareFaces[face][i];
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