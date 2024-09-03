#include <iostream>
#include <stb/stb_image.h>
#include "Texture.h"

namespace Graphics
{
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureId);
		m_HasGen = false;
	}

	void Texture::Load(const char* textureFileName)
	{
		if (!m_HasGen)
		{
			glGenTextures(1, &m_TextureId);
			m_HasGen = true;
		}
		
		Bind();

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		stbi_set_flip_vertically_on_load(true);
		const unsigned char* data = stbi_load(textureFileName, &m_Width, &m_Height, &m_Nch, 0);

		if (data == nullptr)
		{
			std::cerr << "Error: Failed to load texture! <FileName: " << textureFileName << ">\n";
			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}

		GLint format = (m_Nch == 3) ? GL_RGB : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		Unbind();
	}
}
