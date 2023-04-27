#pragma once
#include <GLFW/glfw3.h>

class CoordinateAxes
{
public:
	CoordinateAxes();
	void DrawCoordinateAxes() const;
private:
	static void DrawOX();
	static void DrawOY();
};