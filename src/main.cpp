#include "Core/App.h"
#include "main.h"

int main(int argc, char* argv[]) {

	set_omp_threads(argc, argv);

	OKE3D::App app(800, 800, "Open Krauze Rendrer");
	return app.run();
}
