#pragma comment (lib, "opengl32.lib")

#include <thread>

#include "App.h"
#include <omp.h>

int main() {
	const unsigned int threads = std::thread::hardware_concurrency();
	omp_set_num_threads(threads);

	App* app = new App();
	return app->run();
}