#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "../Math/Glm.h"

namespace Engine
{
	namespace Graphics
	{

		using namespace Math;

		struct Vertex
		{
			Vector3 position;
			Vector3 normal;
			Vector2 texcoord;
		};

		typedef std::vector<Vertex> Vertices;
		typedef std::vector<unsigned int> Indices;

		class Mesh
		{
		public:
			Mesh() = default;
			Mesh(const Vertices& vertices, const Indices& indices);
			~Mesh();

			void SetData(const Vertices& vertices, const Indices& indices);
			void Bind() const;
			void UnBind() const;

			inline unsigned int GetCount() const { return m_Indices.size(); }

		private:
			unsigned int vao, vbo, ibo;
			Vertices m_Vertices;
			Indices m_Indices;

			void SetupMesh();
			void DestroySelf();
		};

	}
}


