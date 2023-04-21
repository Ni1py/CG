#pragma once
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct PointGL {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct ColorRGB {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

class CPin
{
public:
	CPin(PointGL translate, PointGL scale, ColorRGB hatColor);
	void DrawPin() const;
private:
	PointGL m_translate;
	PointGL m_scale;
	ColorRGB m_hatColor;

	static void DrawEllipse(float xCenter, float yCenter, float rx, float ry, float countPi = 2.0f, int points = 360);
	static void DrawHand();
	static void DrawLeg();
	static void DrawBeak(); 
	static void DrawEye();
	static void DrawHat(ColorRGB hatColor);
	static void DrawGlasses();
};
