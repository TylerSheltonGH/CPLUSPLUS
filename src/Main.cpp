#include "Application.h"
#include <iostream>

int main(int argc, char** argv) {
	Application* MainApplication = new Application();

	MainApplication->Init();

	MainApplication->Run();

	MainApplication->~Application();

	return 0;
}