#include "Mesh.h"



namespace Engine
{
	namespace Graphics
	{

		Mesh::Mesh(const Vertices& vertices, const Indices& indices)
		{
			SetData(vertices, indices);
		}

		Mesh::~Mesh()
		{
			DestroySelf();
		}

		void Mesh::SetData(const Vertices& vertices, const Indices& indices)
		{
			m_Vertices = vertices;
			m_Indices = indices;

			/*
			for (auto v : m_Vertices)
			{
				std::cout << "Position(" 
					<< v.position.x << ", "
					<< v.position.y << ", "
					<< v.position.z
					<< ")"
					<< std::endl;

				std::cout << "Normal("
					<< v.normal.x << ", "
					<< v.normal.y << ", "
					<< v.normal.z
					<< ")"
					<< std::endl;

				std::cout << "TexCoord("
					<< v.texcoord.x << ", "
					<< v.texcoord.y
					<< ")"
					<< std::endl;
				
			}
			*/
			

			SetupMesh();
		}

		void Mesh::SetupMesh()
		{
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ibo);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Indices.size(), &m_Indices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void Mesh::Bind() const
		{
			glBindVertexArray(vao);
		}

		void Mesh::UnBind() const
		{
			glBindVertexArray(0);
		}

		void Mesh::DestroySelf()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
		}

	}
}