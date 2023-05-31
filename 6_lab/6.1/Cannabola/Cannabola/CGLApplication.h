#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "inc.h"
#include "BaseApplication.h"
#include "ProgramImpl.h"

struct Size
{
	float width;
	float height;
};

class CGLApplication : public BaseApplication
{
public:
	CGLApplication(char const* title, Size windowSize);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;

private:
	void InitShaders();

	Program m_program;
	Size m_windowSize;
};
