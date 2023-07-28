#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) Error::GLClearError();\
	x;\
	ASSERT(Error::GLLogCall(#x, __FILE__, __LINE__))

class Error
{
public:
	static void TerminateApplication(int Code = -1);

	static void GLClearError();

	static bool GLLogCall(const char* Function, const char* File, int Line);
};