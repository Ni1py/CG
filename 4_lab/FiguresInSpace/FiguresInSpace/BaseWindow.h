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

	virtual void OnResize(
		[[maybe_unused]] int width, [[maybe_unused]] int height) {}
	virtual void Draw(int width, int height) = 0;
	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
};
