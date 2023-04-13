#include <GLFW/glfw3.h>
#include <stdexcept>

#define _USE_MATH_DEFINES
#include <math.h>

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ CreateWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

private:
	virtual void Draw(int width, int height) = 0;

	static GLFWwindow* CreateWindow(int w, int h, const char* title)
	{
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);

		DrawPin(width, height);
	}

	static void DrawPin(int windowWidth, int windowHeight)
	{
		//Рисуем левую руку
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(-0.5, 0.4, 0.0);
		glRotatef(100, 0.0, 0.0, 1.0);
		DrawHand();

		//Рисуем правую руку
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.5, -0.3, 0.0);
		glRotatef(-60, 0.0, 0.0, 1.0);
		DrawHand();

		//Рисуем левую ногу
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(-0.3, -0.3, 0.0);
		glRotatef(-70, 0.0, 0.0, 1.0);
		glScalef(0.5, 0.5, 1);
		DrawLeg();

		//Рисуем тело
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawEllipse(0.0f, 0.0f, 0.5f, 0.5f);

		//Рисуем живот
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glRotatef(200, 0.0, 0.0, 1.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(0.0f, 0.0f, 0.47f, 0.47f, 0.5);

		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(-0.15, -0.31, 0.0);
		glRotatef(-25, 0.0, 0.0, 1.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawEllipse(0.0f, 0.0f, 0.35f, 0.5f, 1.0);

		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(-0.15, -0.32, 0.0);
		glRotatef(-25, 0.0, 0.0, 1.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(0.0f, 0.0f, 0.314f, 0.23f, 1.0);

		//Рисуем клюв
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.05, 0.18, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		glScalef(0.3, 0.3, 1);
		DrawBeak(windowWidth, windowHeight);

		//Рисуем глаза
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.01, 0.35, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		glScalef(0.8, 0.8, 1);
		DrawEye();

		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.18, 0.3, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		glScalef(0.8, 0.8, 1);
		DrawEye();

		//Рисуем шляпу
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.15, 0.51, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		glScalef(0.5, 0.5, 1);
		DrawHat();

		//Рисуем очки
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.13, 0.45, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		glScalef(0.3, 0.3, 1);
		DrawGlasses();

		//Рисуем правую ногу
		glLoadIdentity();
		SetupProjectionMatrix(windowWidth, windowHeight);
		glTranslatef(0.0, -0.4, 0.0);
		glRotatef(-50, 0.0, 0.0, 1.0);
		glScalef(0.5, 0.5, 1);
		DrawLeg();
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		// Вычисляет матрицу ортографического преобразования такую, чтобы вписать квадратную область
		// [-1;+1] по обеим осям внутрь видового порта размером width*height пикселей
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		const double aspectRatio = double(width) / double(height);
		double viewWidth = 2.0;
		double viewHeight = viewWidth;
		if (aspectRatio > 1.0)
		{
			viewWidth = viewHeight * aspectRatio;
		}
		else
		{
			viewHeight = viewWidth / aspectRatio;
		}
		glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
	}

	/*void DrawCircle(float xCenter, float yCenter, float radius, int steps = 360) 
	{
		const float angle = static_cast<float>(2 * M_PI / steps);
		float xPos = xCenter;
		float yPos = yCenter;
		float prevX = xPos;
		float prevY = yPos - radius;
		for (int i = 0; i < steps; i++)
		{
			float newX = radius * sin(angle * i);
			float newY = -radius * cos(angle * i);

			glBegin(GL_TRIANGLES);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2d(xCenter, yCenter);
			glVertex2d(prevX, prevY);
			glVertex2d(newX, newY);
			glEnd();
		}
	}*/
	static void DrawEllipse (float xCenter, float yCenter, float rx, float ry, float countPi = 2.0f, int points = 360)
	{
		const float step = static_cast<float>(M_PI * countPi / points);

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2d(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = 0; angle <= M_PI * countPi; angle += step)
		{
			float a = (fabsf(static_cast<float>(angle - M_PI * countPi)) < 1e-5) ? 0 : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	static void DrawHand()
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawEllipse(0.0f, 0.0f, 0.4f, 0.4f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(0.2f, 0.0, 0.45f, 0.25f);
	}

	static void DrawLeg()
	{
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, -0.4f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.2f, 0.0f);
			glVertex2f(0.2f, -0.6f);
			glVertex2f(-0.5f, -0.7f);
			glVertex2f(-0.5f, -0.3f);			
		glEnd();
		glLineWidth(4);
		glBegin(GL_LINE_STRIP);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, -0.4f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.2f, 0.0f);
			glVertex2f(0.2f, -0.6f);
			glVertex2f(-0.5f, -0.7f);
			glVertex2f(-0.5f, -0.3f);
		glEnd();
	}

	static void DrawBeak(int windowWidth, int windowHeight) {
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawEllipse(-0.6f, 0.0f, 0.2f, 0.2f);

		glColor3f(1.0f, 0.0f, 0.0f);
		DrawEllipse(0.6f, 0.0f, 0.2f, 0.2f);

		glPushMatrix();
		glRotatef(180, 0.0, 0.0, 1.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawEllipse(0.0f, 0.4f, 0.3f, 0.2f, 1.0f);
		glPopMatrix();

		glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-0.6f, 0.2f);
			glVertex2f(-0.6f, -0.2f);
			glVertex2f(-0.3f, -0.4f);
			glVertex2f(0.3f, -0.4f);
			glVertex2f(0.6f, -0.2f);
			glVertex2f(0.6f, 0.2f);
			glVertex2f(0.05f, 0.4f);
			glVertex2f(-0.05f, 0.4f);
		glEnd();
	}

	static void DrawEye()
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(0.0f, 0.0f, 0.1, 0.14);
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawEllipse(0.0f, 0.0f, 0.03, 0.03);
	}

	static void DrawHat()
	{
		//glColor3f(0.5f, 0.2f, 0.0f); //супер дерево
		glColor3f(0.7f, 0.4f, 0.0f);
		DrawEllipse(-0.8f, 0.0f, 0.3f, 0.3f);

		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(-0.7f, 0.3f, 0.4f, 0.4f);

		glColor3f(0.7f, 0.4f, 0.0f);
		DrawEllipse(0.8f, 0.0f, 0.3f, 0.3f);

		glColor3f(1.0f, 1.0f, 1.0f);
		DrawEllipse(0.7f, 0.3f, 0.4f, 0.4f);

		glColor3f(0.7f, 0.4f, 0.0f);
		DrawEllipse(0.0f, 0.3f, 0.4f, 0.3f, 1.0f);

		glBegin(GL_POLYGON);
		glColor3f(0.7f, 0.4f, 0.0f);
		glVertex2f(-0.6f, -0.3f);
		glVertex2f(-0.4f, 0.31f);
		glVertex2f(0.4f, 0.31f);
		glVertex2f(0.6f, -0.3f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.7f, 0.4f, 0.0f);
		glVertex2f(-0.5f, -0.3f);
		glVertex2f(-0.8f, -0.3f);
		glVertex2f(-0.8f, -0.1f);
		glVertex2f(-0.5f, -0.1f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.7f, 0.4f, 0.0f);
		glVertex2f(0.5f, -0.3f);
		glVertex2f(0.8f, -0.3f);
		glVertex2f(0.8f, -0.1f);
		glVertex2f(0.5f, -0.1f);
		glEnd();
	}

	static void DrawGlasses()
	{
		glColor3f(0.5f, 0.2f, 0.0f);

		DrawEllipse(-0.2f, 0.0f, 0.3f, 0.3f);

		DrawEllipse(0.2f, 0.0f, 0.3f, 0.3f);

		glBegin(GL_POLYGON);
		glColor3f(0.5f, 0.2f, 0.0f);
		glVertex2f(-0.2f, 0.3f);
		glVertex2f(-0.8f, 0.3f);
		glVertex2f(-0.8f, -0.3f);
		glVertex2f(0.2f, -0.3f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5f, 0.2f, 0.0f);
		glVertex2f(0.2f, 0.3f);
		glVertex2f(0.8f, 0.3f);
		glVertex2f(0.8f, -0.3f);
		glVertex2f(0.2f, -0.3f);
		glEnd();

		glColor3f(0.5f, 1.0f, 1.0f);

		DrawEllipse(-0.2f, 0.0f, 0.15f, 0.15f);

		glBegin(GL_QUADS);
		glVertex2f(-0.2f, 0.15f);
		glVertex2f(-0.6f, 0.15f);
		glVertex2f(-0.6f, -0.15f);
		glVertex2f(-0.2f, -0.15f);
		glEnd();

		DrawEllipse(0.2f, 0.0f, 0.15f, 0.15f);

		glBegin(GL_QUADS);
		glVertex2f(0.2f, 0.15f);
		glVertex2f(0.6f, 0.15f);
		glVertex2f(0.6f, -0.15f);
		glVertex2f(0.2f, -0.15f);
		glEnd();
	}
};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 800, 600, "Hello, Pin!" };
	window.Run();
}
