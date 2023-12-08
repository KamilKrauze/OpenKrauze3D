#ifndef CORE_H
#define CORE_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Core
{
protected:
	GLFWwindow* window;

/* Construction / Deconstruction */
protected:
	Core();
	~Core() = default;

/* Static Functions */
protected:

	/* Error callback, outputs error to stl error stream. */
	static void error_callback(int error, const char* description) {
		fputs(description, stderr);
	}

	/* Display the version of OpenGL and hardware used. */
	static void display_version() {
		int maj_ver, min_ver;
		glGetIntegerv(GL_MAJOR_VERSION, &maj_ver);
		glGetIntegerv(GL_MINOR_VERSION, &min_ver);

		std::cout << "OpenGL Version = " << maj_ver << "." << min_ver << "\n";

		// Hardware details
		std::cout << "Vender: " << glGetString(GL_VENDOR) << "\n";
		std::cout << "Version:" << glGetString(GL_VERSION) << "\n";
		std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
	}
};

#endif