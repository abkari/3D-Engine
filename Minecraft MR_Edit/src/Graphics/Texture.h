#pragma once

#include <glad/glad.h>

namespace Graphics
{
	class Texture
	{
	public:
		Texture()  : m_TextureId(0), m_Width(0), m_Height(0), m_Nch(0) {}
		~Texture();

		void Load(const char* textureFileName);

		inline void Bind(GLenum activeTextuteSlot = GL_TEXTURE0) const {
			glActiveTexture(activeTextuteSlot);
			glBindTexture(GL_TEXTURE_2D, m_TextureId); 
		}
		inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		inline const int& GetWidth() const { return m_Width; }
		inline const int& GetHeight() const { return m_Height; }
		inline const int& GetNumOfChannels() const { return m_Nch; }

	private:
		bool m_HasGen = false;
		unsigned int m_TextureId;
		int m_Width, m_Height, m_Nch;
		
	};
}