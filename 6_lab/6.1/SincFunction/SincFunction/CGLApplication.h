#pragma once

#include "inc.h"
#include "BaseApplication.h"
#include "ProgramImpl.h"

class CGLApplication : public BaseApplication
{
public:
	CGLApplication(char const* title);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;

private:
	void InitShaders();

	Program m_program;
};
