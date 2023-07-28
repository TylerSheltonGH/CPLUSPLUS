#include "Shader.h"
#include "Log.h"


Shader::Shader() :
	m_AttributeIndex(0),
	m_ProgramID(0),
	m_VertexID(0),
	m_FragmentID(0)
{
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::Create(const std::string& Vertex, const std::string& Fragment)
{
	m_ProgramID = glCreateProgram();

	m_VertexID = Compile(Vertex, GL_VERTEX_SHADER);
	m_FragmentID = Compile(Fragment, GL_FRAGMENT_SHADER);
}

unsigned int Shader::Compile(const std::string& Source, unsigned int Type)
{
	unsigned int id = glCreateShader(Type);
	const char* src = Source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		VOID_CORE_ERROR("Failed to compile shader.");
		VOID_CORE_CRITICAL(message);

		glDeleteShader(id);

		return 0;
	}

	return id;
}

void Shader::Link()
{
	glAttachShader(m_ProgramID, m_VertexID);
	glAttachShader(m_ProgramID, m_FragmentID);

	glLinkProgram(m_ProgramID);

	glValidateProgram(m_ProgramID);

	int result;
	glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(m_ProgramID, length, &length, message);

		glDeleteProgram(m_ProgramID);
		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);

		VOID_CORE_ERROR("Failed to link shader.");
		VOID_CORE_CRITICAL(message);
	}

	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);

	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
}

void Shader::Use()
{
	glUseProgram(m_ProgramID);
	for (int i = 0; i < m_AttributeIndex; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Shader::Unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_AttributeIndex; i++) {
		glDisableVertexAttribArray(i);
	}
}

void Shader::AddAttribute(const std::string& Attribute)
{
	glBindAttribLocation(m_ProgramID, m_AttributeIndex++, Attribute.c_str());
}

int Shader::GetUniformLocation(const std::string& Uniform)
{
	int location = glGetUniformLocation(m_ProgramID, Uniform.c_str());
	if (location == GL_INVALID_INDEX) {
		VOID_CORE_CRITICAL("Uniform {} not found in shader.", Uniform);
	}
	return location;
}