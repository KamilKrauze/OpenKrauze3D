#ifndef INPUTS_H
#define INPUTS_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Inputs {
	namespace Keyboard
	{
		/* Key response callback */
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	namespace Mouse
	{
		/* Mouse button callback */
		static void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods) { }
		
		/* Cursor position callback function */
		static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos) { }
	}
}

#endif // !INPUTS_H
