#pragma once

#include <vector>

#include "glad/glad.h"

#include "Math/Vectors.h"
#include "Math/Matrices.h"

#include "Graphics/Shader.h"
#include "Components/Transform.h"


using namespace Graphics;
using namespace Components;

struct Line
{
	Vector3f StartPoint;
	Vector3f EndPoint;

	Line(const Vector3f& startPoint, const Vector3f& endPoint)
		: StartPoint(startPoint), EndPoint(endPoint) {}
};

typedef std::vector<Line> Lines;
typedef std::vector<unsigned int> LinesIndices;

class Grid
{
public:
	Grid() : m_GridSize(8) {};
	~Grid();

	void Init();
	void Draw(const Matrix4f& view, const Matrix4f& proj);

private:
	int m_GridSize;
	unsigned int m_VAO, m_VBO, m_IBO;
	Shader m_LineShader;
	Lines m_Lines;
	LinesIndices m_LinesIndices;
	Transform m_GridTransform;


};