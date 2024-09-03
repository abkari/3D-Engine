#include "Grid.h"

Grid::~Grid()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void Grid::Init()
{
	m_LineShader.Load("shaders/Line/Line.vert", "shaders/Line/Line.frag");

	/*m_Lines = {
		Line(
			Vector3f(-4.0f, 0.0f, -4.0f),
			Vector3f(-4.0f, 0.0f,  4.0f)
		),
		Line(
			Vector3f(-3.0f, 0.0f, -4.0f),
			Vector3f(-3.0f, 0.0f,  4.0f)
		),
		Line(
			Vector3f(-2.0f, 0.0f, -4.0f),
			Vector3f(-2.0f, 0.0f,  4.0f)
		),
		Line(
			Vector3f(-1.0f, 0.0f, -4.0f),
			Vector3f(-1.0f, 0.0f,  4.0f)
		),
		Line(
			Vector3f(0.0f, 0.0f, -4.0f),
			Vector3f(0.0f, 0.0f,  4.0f)
		),
	};

	m_LinesIndices =
	{
		0, 1,
		2, 3,
		4, 5,
		6, 7,
		8, 9
	};*/

	int halfGridSize = m_GridSize / 2;
	for (int i = 0, j = 0; i <= m_GridSize; i++, j+=2)
	{
		m_Lines.push_back(Line(
			Vector3f(i - halfGridSize, 0.0f, -halfGridSize),
			Vector3f(i - halfGridSize, 0.0f, halfGridSize)
		));

		m_LinesIndices.push_back(j);
		m_LinesIndices.push_back(j + 1);
	}

	for (int i = 0, j = m_LinesIndices.size(); i <= m_GridSize; i++, j += 2)
	{
		m_Lines.push_back(Line(
			Vector3f(-halfGridSize, 0.0f, i - halfGridSize),
			Vector3f(halfGridSize, 0.0f,  i - halfGridSize)
		));

		m_LinesIndices.push_back(j);
		m_LinesIndices.push_back(j + 1);
	}

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line) * m_Lines.size(), &m_Lines[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(LinesIndices) * m_LinesIndices.size(), &m_LinesIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);

	glBindVertexArray(0);
}

void Grid::Draw(const Matrix4f& view, const Matrix4f& proj)
{
	m_LineShader.Enable();
	m_LineShader.SetUniform("model", m_GridTransform.GetTransformMatrix());
	m_LineShader.SetUniform("view", view);
	m_LineShader.SetUniform("proj", proj);
	m_LineShader.SetUniform("lineColor", Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	glBindVertexArray(m_VAO);
	//glLineWidth(5.0f);
	glDrawElements(GL_LINES, m_LinesIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	m_LineShader.Disable();
}