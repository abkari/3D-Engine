#pragma once

#include <glad/glad.h>

#include "Math/Vectors.h"
#include "Math/Matrices.h"

namespace Graphics
{
	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		void Load(const char* vertexShaderFileName, const char* fragmentShaderFileName);

		inline void Enable() const { glUseProgram(m_ProgramId); }
		inline void Disable() const { glUseProgram(0); }

		void SetUniform(const char* name, const int& value) const;
		void SetUniform(const char* name, const float& value) const;
		void SetUniform(const char* name, const bool& value) const;

		void SetUniform(const char* name, const Vector2f& vec2) const;
		void SetUniform(const char* name, const Vector3f& vec3) const;
		void SetUniform(const char* name, const Vector4f& vec4) const;

		void SetUniform(const char* name, const Matrix2f& mat2) const;
		void SetUniform(const char* name, const Matrix2x3f& mat2x3) const;
		void SetUniform(const char* name, const Matrix2x4f& mat2x4) const;

		void SetUniform(const char* name, const Matrix3x2f& mat3x2) const;
		void SetUniform(const char* name, const Matrix3f& mat3) const;
		void SetUniform(const char* name, const Matrix3x4f& mat3x4) const;

		void SetUniform(const char* name, const Matrix4x2f& mat4x2) const;
		void SetUniform(const char* name, const Matrix4x3f& mat4x3) const;
		void SetUniform(const char* name, const Matrix4f& mat4) const;

	private:
		unsigned int m_ProgramId;

		unsigned int GetShaderId(const char* fileName, GLenum type);
	};
}