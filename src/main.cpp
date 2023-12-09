#pragma comment (lib, "opengl32.lib")

#include "App.h"
#include "main.h"

int main(int argc, char* argv[]) {

	set_omp_threads(argc, argv);

	App* app = new App();
	return app->run();
}