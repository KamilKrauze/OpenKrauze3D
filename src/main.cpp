#include <iostream>

#include "App.h"

#pragma comment(lib, "glfw3.lib")

// Adding OpenGL library
#pragma comment(lib, "opengl32.lib")

int main() {
    App app;
    return app.run();
}