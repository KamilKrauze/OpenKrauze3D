#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#pragma comment(lib, "glfw3.lib")

// Standard libraries
#include <cstddef>
#include <string>

// Thirdparty libraries
#include <glad/glad.h>


namespace Pipeline {
	namespace ShaderBuilder {

		struct ShaderPaths {
			const char* fp_shader; // File path to a single shader file.

			const char* fp_vert; // File path to vertex shader.
			const char* fp_frag; // File path to fragment shader.
			const char* fp_geom; // File path to geometry shader.
			const char* fp_tess; // File path to tesselation shader.

			ShaderPaths() = default;
			
			ShaderPaths
			(
				const char* shader = nullptr, 
				const char* vert,
				const char* frag,
				const char* geom = nullptr,
				const char* tess = nullptr
			) : fp_shader(shader), fp_vert(vert), fp_frag(frag), fp_geom(geom), fp_tess(tess) {}
			
			~ShaderPaths() = default;
		};

		// Loads shader depending what the struct contains.
		GLuint LoadShader(const ShaderPaths filepath);

		/* Load vertex and fragment shader and return the compiled program */
		GLuint LoadShader(const char* vertex_path, const char* fragment_path);

		/* Build shaders from strings containing shader source code */
		GLuint BuildShader(GLenum eShaderType, const std::string& shaderText);

		/* Load vertex and fragment shader and return the compiled program */
		GLuint BuildShaderProgram(std::string vertShaderStr, std::string fragShaderStr);

	}
}

#endif // !SHADER_BUILDER_H

