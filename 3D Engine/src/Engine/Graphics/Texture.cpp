#include "Texture.h"


namespace Engine
{
	namespace Graphics
	{
		Texture::Texture(const char* filename)
		{
			Load(filename);
		}

		Texture::~Texture()
		{
			DestroySelf();
		}

		bool Texture::Load(const char* filename)
		{
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(filename, &m_Width, &m_Height, &m_Nch, NULL);

			if (!data)
			{
				std::cout << "Error: Failed to load texture! - Filename::" << filename << std::endl;
				return false;
			}

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			int texFormat = (m_Nch == 3)? GL_RGB : GL_RGBA;

			glTexImage2D(
				GL_TEXTURE_2D, 
				0, 
				texFormat,
				m_Width, 
				m_Height, 
				NULL, 
				texFormat,
				GL_UNSIGNED_BYTE, 
				data
			);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
			
			return true;
		}

		void Texture::Bind(GLenum textureSlot) const
		{
			glActiveTexture(textureSlot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Texture::UnBind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::DestroySelf()
		{
			glDeleteTextures(1, &id);
		}
	}
}