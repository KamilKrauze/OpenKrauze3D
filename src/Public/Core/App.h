#ifndef APP_H
#define APP_H

#include "Core/Core.h"
#include "Properties/WindowProperties.h"

static OKE3D::Ref<OKE3D::WindowProperties> win_properties;
namespace OKE3D {
	class App : public OKE3D::Core {
	private:
		GLuint shader_program;
		GLuint vao; // Vertex Array Object

		/* Constructors / Deconstructors */
	private:
		App();
	public:
		explicit App(int w, int h, const char* title);
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
			OKE3D::update_window_properties(win_properties.get(), w, h);

			glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
		}
	};
};


#endif // !APP_H
