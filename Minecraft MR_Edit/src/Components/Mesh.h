#pragma once

#include <vector>
#include <glad/glad.h>

#include "Math/Vectors.h"
#include "Graphics/Shader.h"

namespace Components
{
	struct Vertex
	{
		Vector3f Position;
		Vector3f Normal;
		Vector2f Texcoord;
		Vector4f Color;

		Vertex(
			const Vector3f& position = { 0.0f, 0.0f, 0.0f },
			const Vector3f& normal = { 0.0f, 0.0f, 0.0f },
			const Vector2f& texcoord = { 0.0f, 0.0f },
			const Vector4f& color = { 0.0f, 0.0f, 0.0f, 1.0f }
		) : Position(position), Normal(normal), Color(color), Texcoord(texcoord) {}
	};

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<unsigned int> Indices;

	class Mesh
	{
	public:
		Mesh() = default;
		~Mesh();

		void Load(const Vertices& vertices, const Indices& indices);

		inline void Bind() const { glBindVertexArray(m_VAO); }
		inline void Unbind() const { glBindVertexArray(0); }
		inline int GetIndicesCount() const { return m_Indices.size(); }

	private:
		unsigned int m_VAO, m_VBO, m_IBO;

		Vertices m_Vertices;
		Indices m_Indices;

		void SetupMesh();
	};
}


