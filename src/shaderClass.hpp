#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <iostream>
#include <glad/glad.h>

class Shader {
public:
    GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void activate();
	void deactivate();
};
#endif