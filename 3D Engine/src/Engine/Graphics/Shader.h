#pragma once


#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include "../Math/Glm.h"

namespace Engine
{
	namespace Graphics
	{

		using namespace Math;

		std::string read_file(const char* filename);

		class Shader
		{
		public:
			Shader() = default;
			explicit Shader(const char* vertexfilename, const char* fragmentfilename);
			~Shader();

			bool Load(const char* vertexfilename, const char* fragmentfilename);

			void Enable();
			void Disable();

			void SetInteger(const char* name, const int& value) const;
			void SetFloat(const char* name, const float& value) const;
			void SetBool(const char* name, const bool& value) const;

			void SetVector2(const char* name, const Vector2& value) const;
			void SetVector3(const char* name, const Vector3& value) const;
			void SetVector4(const char* name, const Vector4& value) const;

			void SetMat4(const char* name, const Mat4& mat4) const;

		private:
			unsigned int id;
			bool programLinkSuccess;

			unsigned int CompileShader(const char* sourceCode, GLenum type);
			unsigned int LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);

			void DestroySelf();
			
		};

	}

}



