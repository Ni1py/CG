#pragma once

enum class CuboctahedronSide
{
	FRONT_SQUARE_FACE,
	REAR_SQUARE_FACE,
	RIGHT_SQUARE_FACE,
	LEFT_SQUARE_FACE,
	UPPER_SQUARE_FACE,
	LOWER_SQUARE_FACE,
	RIGHT_UPPER_FRONT_TRIANGULAR_FACE,
	LEFT_UPPER_FRONT_TRIANGULAR_FACE,
	LEFT_LOWER_FRONT_TRIANGULAR_FACE,
	RIGHT_LOWER_FRONT_TRIANGULAR_FACE,
	RIGHT_UPPER_REAR_TRIANGULAR_FACE,
	LEFT_UPPER_REAR_TRIANGULAR_FACE,
	LEFT_LOWER_REAR_TRIANGULAR_FACE,
	RIGHT_LOWER_REAR_TRIANGULAR_FACE
};

class Cuboctahedron
{
public:
	// ������� ��� � �������� ������ �������
	explicit Cuboctahedron(float size = 1);
	// ������ ���
	void Draw() const;
	// ������ ���� ������� ����
	void SetSideColor(CuboctahedronSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);

private:
	float m_size;

	// ����� ������ ����
	GLubyte m_sideColors[14][4];
};
