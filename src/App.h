#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Core.h"
class App : public Core
{
private:
	GLuint shader_program;
	GLuint vao; // Vertex Array Object

/* Constructors / Deconstructors */
public:
	App();
	~App();

/* Object instance functions */
private:
	void init();
	void display();

public:
	int run();

/* Static functions */
private:
	/* Window reshape callback
	- Called whenever the window is resized. The new window size is given, in pixels.
	*/
	static void reshape(GLFWwindow* window, int w, int h) {
		glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	}
};


#endif // !APP_H
