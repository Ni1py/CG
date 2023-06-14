#include "Planet.h"
#include "TextureLoader.h"

CPlanet::CPlanet(std::wstring const& textureName, float radius, unsigned slices, unsigned stacks)
	: m_sphere(radius, slices, stacks)
	, m_textureName(textureName)
	, m_rotationAngle(0)
	, m_inclinationAngle(0)
	, m_rotationSpeed(0)
	, m_x(0)
	, m_y(0)
{
	m_material.SetDiffuse(1, 1, 1);
	m_material.SetShininess(50);
	m_material.SetSpecular(1, 1, 1);
}

// Изменяем угол вращения планеты вокруг своей оси
void CPlanet::Animate(float timeDelta, float x, float y)
{
	m_rotationAngle = fmodf(m_rotationAngle + m_rotationSpeed * timeDelta, 360);
	m_x = x;
	m_y = y;
}

void CPlanet::SetInclinationAngle(float inclinationAngle)
{
	m_inclinationAngle = inclinationAngle;
}

void CPlanet::SetRotationSpeed(float rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}

void CPlanet::Draw() const
{
	if (!m_texture)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_texture.Attach(loader.LoadTexture2D(m_textureName));
	}
	// Активизируем текстуру и материал планеты
	glEnable(GL_TEXTURE_2D);
	m_texture.Bind();
	m_material.Activate();

	// Сохраняем текущую матрицу
	// (предполагается работа с матрицей modelview)
	// и поворачиваем планету
	// (сначала вокруг оси вращения, а затем наклоняем ось)

	glPushMatrix();
	
	
	glTranslatef(m_x, m_y, 0);
	glRotatef(m_inclinationAngle, 1, 0, 0);
	glRotatef(m_rotationAngle, 0, 0, 1);
	//glTranslatef(m_x, m_y, 0);
	//glTranslatef(0, 0, 0);
	

	/*glTranslatef(m_x, m_y, 0);
	glRotatef(m_inclinationAngle, 1, 0, 0); смещение поворота каким-то образом
	glRotatef(m_rotationAngle, 0, 0, 1);
	glTranslatef(m_x, m_y, 0);*/

	// рисуем сферу
	m_sphere.Draw();

	// восстанавливаем текущую матрицу
	glPopMatrix();
}
