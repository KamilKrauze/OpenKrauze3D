#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H

#pragma comment(lib, "glfw3.lib")

// Standard libraries
#include <cstddef>
#include <string>

// Thirdparty libraries
#include <glad/glad.h>


namespace Pipeline {
	namespace Shader {

		struct ShaderPaths {
			const char* fp_vert; // File path to vertex shader.
			const char* fp_frag; // File path to fragment shader.

			GLuint programID; // The ID of the built shader program.

			ShaderPaths() = default;
			ShaderPaths(const char* vert, const char* frag) : fp_vert(vert), fp_frag(frag) { this->programID = NULL; }
			~ShaderPaths() = default;
		};


		/* Load vertex and fragment shader and return the compiled program */
		GLuint LoadShader(const char* vertex_path, const char* fragment_path);

		/* Build shaders from strings containing shader source code */
		GLuint BuildShader(GLenum eShaderType, const std::string& shaderText);

		/* Load vertex and fragment shader and return the compiled program */
		GLuint BuildShaderProgram(std::string vertShaderStr, std::string fragShaderStr);

	}
}

#endif // !SHADER_PIPELINE_H

