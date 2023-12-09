#include "Core/App.h"
#include "Inputs/Inputs.h"
#include "Pipeline/ShaderBuilder.h"
#include "Globals/API_Defaults.h"

#include <glm/glm.hpp>

OKE3D::App::App() : Core()
{
    shader_program = NULL;
    vao = NULL;

    if (!glfwInit())
        exit(EXIT_FAILURE);
}

OKE3D::App::App(int w, int h, const char* title)
{
	win_properties = std::make_shared<WindowProperties>(w, h, title);

	*this = App();
}

OKE3D::App::~App()
{
}

void OKE3D::App::init()
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

void OKE3D::App::display()
{
	using namespace glm;

	/* Define the background colour */
	glClearColor(0.1, 0.1, 0.1, 1);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Enable depth test  */
	glEnable(GL_DEPTH_TEST);

	//glUseProgram(shader_program);

	/* Turn off program and vertex attribute array after rendering frame */
	glDisableVertexAttribArray(0);
	glUseProgram(0);

}

int OKE3D::App::run()
{
	glfwWindowHint(GLFW_SAMPLES, Globals::API_Defaults::Samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Globals::API_Defaults::MajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Globals::API_Defaults::MinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/* Register the error callback first to enable any GLFW errors to be processed. */
	glfwSetErrorCallback(this->error_callback);

	/* Create a GLFW window, bail out if it doesn't work */
	this->window = glfwCreateWindow(win_properties->width, win_properties->height, win_properties->title, NULL, NULL);
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
