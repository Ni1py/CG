#include "MonkeySaddleSurface.h"

CMonkeySaddleSurface::CMonkeySaddleSurface(
	int columns, int rows, float xMin, float xMax, float yMin, float yMax)
	:CSurface(columns, rows, xMin, xMax, yMin, yMax)
{
}

Vertex CMonkeySaddleSurface::CalculateVertex(double x, double y)const
{
	// ��������� �������� ���������� z
	double z = x * x * x - 3 * x * y * y;

	// ��������� ���������
	Vertex result =
	{
		// ���������� �������
		float(x), float(y), float(z),
		// �������� ������ ������� � ��������� �����
		float(0), float(0), float(0)
	};
	return result;
}
