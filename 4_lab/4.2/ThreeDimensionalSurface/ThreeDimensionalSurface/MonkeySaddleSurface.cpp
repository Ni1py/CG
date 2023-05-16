#include "MonkeySaddleSurface.h"

CMonkeySaddleSurface::CMonkeySaddleSurface(
	int columns, int rows, float xMin, float xMax, float yMin, float yMax)
	:CSurface(columns, rows, xMin, xMax, yMin, yMax)
{
}

Vertex CMonkeySaddleSurface::CalculateVertex(double x, double y)const
{
	// вычисляем значение координаты z
	double z = x * x * x - 3 * x * y * y;

	// формируем результат
	Vertex result =
	{
		// координаты вершины
		float(x), float(y), float(z),
		// приводим вектор нормали к единичной длине
		float(0), float(0), float(0)
	};
	return result;
}
