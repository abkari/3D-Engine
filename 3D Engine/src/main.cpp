#include "Engine.h"

int main(int argc, const char* argv)
{

	// Create Our App
	auto* app = new Engine::Application;
	app->Run();

	// Clear Sttuf
	delete app;
	app = nullptr;

	return 0;
}
