#include "shader.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

shader::shader(const char* vertexPath, const char* fragmentPath) {
	Init(vertexPath, fragmentPath);
}

void shader::Init(const char* vertexPath, const char* fragmentPath) {
	
	std::string vertexCode;
	std::string fragmentCode;
	
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// compile shaders
	unsigned int vertex, fragment;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	checkCompileErrors(m_ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void shader::use()  {
	glUseProgram(m_ID);
}

void shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void shader::setMatrix4fv(const std::string& name, float* value) const {
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1,GL_FALSE,value);
}

void shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[512];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --- -- " << std::endl;
		}
	}
}