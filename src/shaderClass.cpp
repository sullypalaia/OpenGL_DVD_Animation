#include "./shaderClass.hpp"

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
	const char *vertexSource = vertexFile;
	const char *fragmentSource = fragmentFile;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::activate() {
	glUseProgram(ID);
}

void Shader::deactivate() {
	glDeleteProgram(ID);
}