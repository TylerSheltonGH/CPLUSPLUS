#pragma once
#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void Create(const std::string& Vertex, const std::string& Fragment);

	unsigned int Compile(const std::string& Source, unsigned int Type);

	void Link();

	void Use();

	void Unuse();

	void AddAttribute(const std::string& Attribute);

	int GetUniformLocation(const std::string& Uniform);

private:
	int m_AttributeIndex;
	unsigned int m_ProgramID;
	unsigned int m_VertexID;
	unsigned int m_FragmentID;
};