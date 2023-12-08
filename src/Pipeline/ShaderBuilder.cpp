#include "ShaderBuilder.h"

#include "../Core/Sanitize.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>

enum class ShaderCombination {
	NONE, // No files.

	VERT_FRAG,				// Separate vert and frag files only.
	VERT_FRAG_GEOM,			// Separate vert, frag, and geometry files only.
	VERT_FRAG_TESS,			// Separate vert, frag, and tesselation files only.
	VERT_FRAG_GEOM_TESS,	// Separate vert, frag, geometry, and tesselation files.
	
	SINGLE,					// Single file with vert and frag.
	SINGLE_GEOM,			// Single file with vert and frag shader, and separate geometry shader.
	SINGLE_TESS,			// Single file with vert and frag shader, and separate tesselation shader.
	SINGLE_GEOM_TESS,		// Single file with vert and frag shader, and separate geometry and tesselation shaders.
	
	SINGLE_INC_GEOM,		// Single file with vert, frag, and geometry shader.
	SINGLE_INC_TESS,		// Single file with vert, frag, and tesselation shader.
	SINGLE_INC_ALL			// Single file with vert, frag, geometry, and tesselation shader.
};

// Read text in file helper function
std::string readFile(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint Pipeline::Shader::LoadShader(const ShaderPaths filepath)
{
	GLuint shaderID = NULL;
	ShaderCombination combination = ShaderCombination::NONE;

	// Separate files
	if (checkptr(filepath.fp_vert) && checkptr(filepath.fp_frag))
	{
		combination = ShaderCombination::VERT_FRAG;

		if (checkptr(filepath.fp_geom)) {
			combination = ShaderCombination::VERT_FRAG_GEOM;
		}

		if (checkptr(filepath.fp_tess)) {
			switch (combination) {
			case ShaderCombination::VERT_FRAG_GEOM:
				combination = ShaderCombination::VERT_FRAG_GEOM_TESS;
				break;
			
			default:
				combination = ShaderCombination::VERT_FRAG_TESS;
				break;
			}
		}
	}

	// Single with optional separate files
	else if (checkptr(filepath.fp_shader)) {
		
		combination = ShaderCombination::SINGLE;

		if (checkptr(filepath.fp_geom)) {
			combination = ShaderCombination::SINGLE_GEOM;
		}

		if (checkptr(filepath.fp_tess)) {
			switch (combination) {
			case ShaderCombination::SINGLE_GEOM:
				combination = ShaderCombination::SINGLE_GEOM_TESS;
				break;

			default:
				combination = ShaderCombination::SINGLE_TESS;
				break;
			}
		}
	}

	// Throw error if none found
	if (combination == ShaderCombination::NONE) throw std::runtime_error("ERROR: No shaders specified");

	// Select shader loader
	std::string vert, frag, geom, tess;
	switch (combination) {
	case ShaderCombination::VERT_FRAG:
		shaderID = LoadShader(filepath.fp_vert, filepath.fp_frag);
		break;

	case ShaderCombination::VERT_FRAG_GEOM:
		break;

	case ShaderCombination::VERT_FRAG_TESS:
		break;

	case ShaderCombination::VERT_FRAG_GEOM_TESS:
		break;

	case ShaderCombination::SINGLE:
		// Read file and create separate intermediary files.
		// Load shader
		shaderID = LoadShader(vert.c_str(), frag.c_str());
		break;

	case ShaderCombination::SINGLE_GEOM:
		break;

	case ShaderCombination::SINGLE_TESS:
		break;

	case ShaderCombination::SINGLE_GEOM_TESS:
		break;
	}

	return shaderID;
}

GLuint Pipeline::Shader::LoadShader(const char* vertex_path, const char* fragment_path)
{
	GLuint vertShader, fragShader;

	// Read shaders
	std::string vertShaderStr = readFile(vertex_path);
	std::string fragShaderStr = readFile(fragment_path);

	GLint result = GL_FALSE;
	int logLength;

	vertShader = BuildShader(GL_VERTEX_SHADER, vertShaderStr);
	fragShader = BuildShader(GL_FRAGMENT_SHADER, fragShaderStr);

	std::cout << "Linking program:\n" << vertex_path + '\n' << "\n" << fragment_path + '\n' << "\n" << std::endl;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	if (!&programError[0]) {
		std::cout << &programError[0] << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

GLuint Pipeline::Shader::BuildShader(GLenum eShaderType, const std::string& shaderText)
{
	GLuint shader = glCreateShader(eShaderType);
	const char* strFileData = shaderText.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Output the compile errors

		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char* strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		std::cerr << "Compile error in " << strShaderType << "\n\t" << strInfoLog << std::endl;
		delete[] strInfoLog;

		throw std::runtime_error("Shader compile exception");
	}

	return shader;
}

GLuint Pipeline::Shader::BuildShaderProgram(std::string vertShaderStr, std::string fragShaderStr)
{
	GLuint vertShader, fragShader;
	GLint result = GL_FALSE;

	try
	{
		vertShader = BuildShader(GL_VERTEX_SHADER, vertShaderStr);
		fragShader = BuildShader(GL_FRAGMENT_SHADER, fragShaderStr);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		throw std::exception("BuildShaderProgram() Build shader failure. Abandoning");
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{

		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		std::cerr << "Linker error: " << strInfoLog << std::endl;

		delete[] strInfoLog;
		throw std::runtime_error("Shader could not be linked.");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}
