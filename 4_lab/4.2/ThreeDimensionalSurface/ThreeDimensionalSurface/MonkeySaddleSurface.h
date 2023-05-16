#pragma once

#include "Surface.h"

class CMonkeySaddleSurface : public CSurface
{
public:
	CMonkeySaddleSurface(
		int columns, int rows, float xMin, float xMax, float yMin, float yMax);
protected:
	// переопределяем метод вычисления вершины сетки
	Vertex CalculateVertex(double x, double y)const override;
};
