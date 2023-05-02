#pragma once

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title);

	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow();

	glm::ivec2 GetFramebufferSize() const;

	void Run();

private:
	static BaseWindow* GetBaseWindow(GLFWwindow* window);

	//для настройки проекционной матрицы, чтобы вовремя изменения размеров окна, отрисовка не вытягивалась
	virtual void OnResize(int width, int height) {}

	//для изменения матрицы камер
	virtual void OnMouseButton(int button, int action, int mods) {}
	virtual void OnMouseMove(double x, double y) {}

	virtual void Draw(int width, int height) = 0;
	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
};
