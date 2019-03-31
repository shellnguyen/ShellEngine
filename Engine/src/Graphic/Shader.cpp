#include <stdio.h>
#include "Shader.h"
#include "GL\glew.h"

unsigned int Shader::LoadShader(unsigned int type, const char* path)
{
	unsigned int shader;
	int compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	FILE * pf;
	if (fopen_s(&pf, path, "rb") != 0)
		return NULL;
	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char * shaderSrc = new char[size + 1];
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = 0;
	fclose(pf);

	glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
	delete[] shaderSrc;

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		int infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];


			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error compiling shader:\n%s\n", infoLog);
			//Debug("Error compiling shader:\n%s\n", infoLog);

			delete[] infoLog;
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int Shader::LoadProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId)
{
	unsigned int programObject;
	int linked;

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vertexShaderId);
	glAttachShader(programObject, fragmentShaderId);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		int infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[sizeof(char) * infoLen];

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);
			//Debug("Error linking program:\n%s\n", infoLog);

			delete infoLog;
		}

		glDeleteProgram(programObject);
		return 0;
	}

	return programObject;
}

template <template T>
void Shader::SetAttribute(const char* attribute, T value)
{
}

