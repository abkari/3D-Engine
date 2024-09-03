#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

namespace Graphics
{
	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramId);
	}

	void Shader::Load(const char* vertexShaderFileName, const char* fragmentShaderFileName)
	{
		unsigned int vertexShaderId = GetShaderId(vertexShaderFileName, GL_VERTEX_SHADER);
		unsigned int fragmentShaderId = GetShaderId(fragmentShaderFileName, GL_FRAGMENT_SHADER);

		m_ProgramId = glCreateProgram();
		glAttachShader(m_ProgramId, vertexShaderId);
		glAttachShader(m_ProgramId, fragmentShaderId);
		glLinkProgram(m_ProgramId);

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		int success;
		char infoLog[1024];

		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(m_ProgramId, 1024, NULL, infoLog);
			std::cerr << "Error: Failed to link program!\n" << infoLog << "\n";
		};
	}

	unsigned int Shader::GetShaderId(const char* fileName, GLenum type)
	{
		// Create shader
		unsigned int shader = glCreateShader(type);

		// Read shader file
		std::ifstream file(fileName);
		std::string content;

		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
				content += line + "\n";
			file.close();
		}
		else
			std::cerr << "Error: Failed to open file! <Filename:" << fileName << ">\n";

		// Compile shader
		const char* shaderSource = content.c_str();

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		// Check for shader errors
		int success;
		char infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);

			switch (type)
			{
			case GL_VERTEX_SHADER:
				std::cerr << "Error: Failed to compile vertex shader!\n" << infoLog << "\n";
				break;
			case GL_FRAGMENT_SHADER:
				std::cerr << "Error: Failed to compile fragment shader!\n" << infoLog << "\n";
				break;
			}
		};

		// Return shader
		return shader;
	}

	void Shader::SetUniform(const char* name, const int& value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgramId, name), value);
	}

	void Shader::SetUniform(const char* name, const float& value) const
	{
		glUniform1f(glGetUniformLocation(m_ProgramId, name), value);
	}

	void Shader::SetUniform(const char* name, const bool& value) const
	{
		SetUniform(name, (int)value);
	}

	void Shader::SetUniform(const char* name, const Vector2f& vec2) const
	{
		glUniform2fv(glGetUniformLocation(m_ProgramId, name), 1, &vec2[0]);
	}

	void Shader::SetUniform(const char* name, const Vector3f& vec3) const
	{
		glUniform3fv(glGetUniformLocation(m_ProgramId, name), 1, &vec3[0]);
	}

	void Shader::SetUniform(const char* name, const Vector4f& vec4) const
	{
		glUniform4fv(glGetUniformLocation(m_ProgramId, name), 1, &vec4[0]);
	}

	void Shader::SetUniform(const char* name, const Matrix2f& mat2) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat2));
	}

	void Shader::SetUniform(const char* name, const Matrix2x3f& mat2x3) const
	{
		glUniformMatrix2x3fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat2x3));
	}

	void Shader::SetUniform(const char* name, const Matrix2x4f& mat2x4) const
	{
		glUniformMatrix2x4fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat2x4));
	}

	void Shader::SetUniform(const char* name, const Matrix3x2f& mat3x2) const
	{
		glUniformMatrix3x2fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat3x2));
	}

	void Shader::SetUniform(const char* name, const Matrix3f& mat3) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat3));
	}

	void Shader::SetUniform(const char* name, const Matrix3x4f& mat3x4) const
	{
		glUniformMatrix3x4fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat3x4));
	}

	void Shader::SetUniform(const char* name, const Matrix4x2f& mat4x2) const
	{
		glUniformMatrix4x2fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat4x2));
	}

	void Shader::SetUniform(const char* name, const Matrix4x3f& mat4x3) const
	{
		glUniformMatrix4x3fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat4x3));
	}

	void Shader::SetUniform(const char* name, const Matrix4f& mat4) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(mat4));
	}
}
