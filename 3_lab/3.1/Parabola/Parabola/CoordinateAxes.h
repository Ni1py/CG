#pragma once
#include <GLFW/glfw3.h>

class CoordinateAxes
{
public:
	CoordinateAxes();
	void Draw() const;
private:
	static void DrawOX();
	static void DrawOY();
};