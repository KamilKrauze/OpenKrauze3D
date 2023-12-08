#pragma comment (lib, "opengl32.lib")

#include "App.h"

int main() {
	App* app = new App();
	return app->run();
}