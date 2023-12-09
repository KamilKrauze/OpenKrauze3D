#ifndef WINDOW_PROPERTIES_H
#define WINDOW_PROPERTIES_H

#include <glad/glad.h>
#include <cstddef>

// Stores window information i.e window width, window height, etc.
namespace OKE3D {
	struct WindowProperties {

		const char* title; // Window title
		GLuint width; // Window width
		GLuint height; // Window height

		/*
		Window aspect ratio:
		 - To scale objects within a scene proportionally to the window dimensions and specified aspect ratio
		*/
		GLfloat aspect_ratio;

		// Initialize struct
		WindowProperties(GLuint w = 800, GLuint h = 800, const char* title = "OpenKrauzeEngine") : width(w), height(h), title(title) { this->aspect_ratio = (GLfloat)this->width / (GLfloat)this->height; }
		~WindowProperties() = default;

	};

	// Computes the aspect ratio by width/height
	static void update_window_properties(WindowProperties* wp, int width, int height)
	{
		wp->width = width;
		wp->height = height;
		wp->aspect_ratio = (GLfloat)width / (GLfloat)height;
	}

	// Computes the aspect ratio by the specified width/height and aspect ratio dimensions.
	// Causes odd object scaling if window width and height aren't the same as the aspect ratio dimensions.
	static void update_window_properties(WindowProperties* wp, int width, int ratio_w, int height, int ratio_h)
	{
		wp->width = width;
		wp->height = height;
		wp->aspect_ratio = ((GLfloat)width * ratio_w) / ((GLfloat)height / ratio_h);
	}
}

#endif // !WINDOW_PROPERTIES_H