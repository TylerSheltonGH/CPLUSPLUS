#include "Error.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Log.h"


void Error::TerminateApplication(int Code)
{
	SDL_Quit();
	exit(Code);
}

void Error::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Error::GLLogCall(const char* Function, const char* File, int Line)
{
	while (GLenum error = glGetError()) {
		VOID_CORE_ERROR("OpenGL Error: {}, Function: {}, File: {}, Line: {}", error, Function, File, Line);
		return false;
	}
	return true;
}
