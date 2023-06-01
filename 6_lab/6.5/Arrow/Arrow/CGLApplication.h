#pragma once

#include "BaseApplication.h"
#include "ProgramImpl.h"
#include "inc.h"

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
};
