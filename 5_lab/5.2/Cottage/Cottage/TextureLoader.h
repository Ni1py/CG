#pragma once

#include "TextureHandle.h"

class TextureLoader
{
public:
	TextureHandle LoadTexture(std::string const& fileName, GLuint level = 0) const;

private:
	GLenum m_minFilter = GL_NEAREST;
	GLenum m_magFilter = GL_NEAREST;
	GLenum m_wrapS = GL_REPEAT;
	GLenum m_wrapT = GL_REPEAT;
};
