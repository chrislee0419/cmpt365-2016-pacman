#pragma once

#include "..\depend\glew\glew.h"
#include "..\depend\freeglut\freeglut.h"
#include <iostream>

namespace Core {
	class ShaderLoader
	{
	private:
		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);

	public:
		ShaderLoader();
		~ShaderLoader();
		GLuint CreateProgram(char* vertexShaderFilename, char* fragmentShaderFilename);
	};
}
	

