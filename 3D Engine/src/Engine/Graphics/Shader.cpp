#include "Shader.h"

namespace Engine
{
	namespace Graphics
	{
		std::string read_file(const char* filename)
		{
			std::string content;
			std::ifstream file(filename);

			if (file.is_open())
			{

				while (file) content += file.get();
				file.close();
			}

			return content;
		}


		Shader::Shader(const char* vertexfilename, const char* fragmentfilename)
		{
			Load(vertexfilename, fragmentfilename);
		}

		Shader::~Shader()
		{
			DestroySelf();
		}

		bool Shader::Load(const char* vertexfilename, const char* fragmentfilename)
		{
			std::string vertexSourceCodeStr = read_file(vertexfilename);
			std::string fragmentSourceCodeStr = read_file(fragmentfilename);

			

			unsigned int vertexShader = CompileShader(vertexSourceCodeStr.c_str(), GL_VERTEX_SHADER);
			unsigned int fragmentShader = CompileShader(fragmentSourceCodeStr.c_str(), GL_FRAGMENT_SHADER);

			id = LinkProgram(vertexShader, fragmentShader);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return programLinkSuccess;
		}

		unsigned int Shader::CompileShader(const char* sourceCode, GLenum type)
		{
			unsigned int shader_id = glCreateShader(type);

			glShaderSource(shader_id, 1, &sourceCode, NULL);
			glCompileShader(shader_id);

			int success;
			char infoLog[1024];

			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
				std::cout << ((type == GL_VERTEX_SHADER)?
					"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" : "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n") 
					<< infoLog << std::endl;
			}

			return shader_id;
		}

		unsigned int Shader::LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
		{
			unsigned int program_id = glCreateProgram();
			glAttachShader(program_id, vertexShader);
			glAttachShader(program_id, fragmentShader);
			glLinkProgram(program_id);


			int success;
			char infoLog[1024];

			glGetProgramiv(program_id, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program_id, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				programLinkSuccess = false;
			}
			else
				programLinkSuccess = true;
			
			return program_id;

		}

		void Shader::Enable()
		{
			glUseProgram(id);
		}

		void Shader::Disable()
		{
			glUseProgram(0);
		}

		void Shader::DestroySelf()
		{
			glDeleteProgram(id);
		}

		void Shader::SetInteger(const char* name, const int& value) const
		{
			glUniform1i(glGetUniformLocation(id, name), value);
		}

		void Shader::SetFloat(const char* name, const float& value) const
		{
			glUniform1f(glGetUniformLocation(id, name), value);
		}

		void Shader::SetBool(const char* name, const bool& value) const
		{
			SetInteger(name, int(value));
		}

		void Shader::SetVector2(const char* name, const Vector2& vec2) const
		{
			glUniform2i(glGetUniformLocation(id, name), vec2.x, vec2.y);
		}

		void Shader::SetVector3(const char* name, const Vector3& vec3) const
		{
			glUniform3i(glGetUniformLocation(id, name), vec3.x, vec3.y, vec3.z);
		}

		void Shader::SetVector4(const char* name, const Vector4& vec4) const
		{
			glUniform4i(glGetUniformLocation(id, name), vec4.x, vec4.y, vec4.z, vec4.a);
		}

		void Shader::SetMat4(const char* name, const Mat4& mat4) const
		{
			glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat4));
		}

	}

}



