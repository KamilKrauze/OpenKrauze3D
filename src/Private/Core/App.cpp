#include "Core/App.h"
#include "Inputs/Inputs.h"
#include "Pipeline/ShaderBuilder.h"

#include <glm/glm.hpp>

App::App() : Core()
{
    shader_program = NULL;
    vao = NULL;

    if (!glfwInit())
        exit(EXIT_FAILURE);
}

App::~App()
{
}

void App::init()
{
    // Generate index (name) for one vertex array object
    glGenVertexArrays(1, &vao);

    // Create the vertex array object and make it current
    glBindVertexArray(vao);

	/* Load and build the vertex and fragment shaders */
	try
	{
		/*shader_program = Pipeline::Shader::LoadShader("./shaders/UVcheckerboard.vert", "./shaders/UVcheckerboard.frag");*/
	}
	catch (std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

}

void App::display()
{
	using namespace glm;

	/* Define the background colour */
	glClearColor(1, 0, 1, 1);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Enable depth test  */
	glEnable(GL_DEPTH_TEST);

	//glUseProgram(shader_program);

	/* Turn off program and vertex attribute array after rendering frame */
	glDisableVertexAttribArray(0);
	glUseProgram(0);

}

int App::run()
{
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/* Register the error callback first to enable any GLFW errors to be processed. */
	glfwSetErrorCallback(this->error_callback);

	/* Create a GLFW window, bail out if it doesn't work */
	this->window = glfwCreateWindow(800, 800, "OpenKrauzeEngine", NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Associate an OpenGL context with the recently created GLFW window */
	glfwMakeContextCurrent(this->window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD. Exiting." << std::endl;
		return -1;
	}


	// Register function pointer for cursor position
	glfwSetCursorPosCallback(this->window, Inputs::Mouse::cursor_position_callback);

	// Register function pointer for mouse button input
	glfwSetMouseButtonCallback(this->window, Inputs::Mouse:: mouse_btn_callback);

	// Register function pointer for key input.
	glfwSetKeyCallback(this->window, Inputs::Keyboard::key_callback);

	// Register function pointer for window resizing.
	glfwSetFramebufferSizeCallback(this->window, this->reshape);

	display_version();

	init();

	/* The main event loop */
	while (!glfwWindowShouldClose(this->window))
	{
		/* Call our own drawing function */
		display();

		/* Swap buffers: GLFW is double buffered as standard */
		glfwSwapBuffers(this->window);

		/* Processes registered events, causes the callbacks to be called.*/
		glfwPollEvents();
	}

	/* Clean up */
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
    return 0;
}
