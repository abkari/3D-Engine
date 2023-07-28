#pragma once

#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>


namespace Engine
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture() = default;
			Texture(const char* filename);
			~Texture();

			bool Load(const char* filename);

			void Bind(GLenum textureSlot = GL_TEXTURE0) const;
			void UnBind() const;

			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }

		private:
			unsigned int id;
			int m_Width;
			int m_Height;
			int m_Nch;

			void DestroySelf();

		};
	}
}



