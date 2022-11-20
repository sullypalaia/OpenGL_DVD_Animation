#ifndef VAO_CLASS_HPP
#define VAO_CLASS_HPP

#include "VBO.hpp"
#include <glad/glad.h>

class VAO {
public:
	GLuint ID;
	VAO();

	void linkVBO(VBO& VBO, GLuint layout);
	void bind();
	void unbind();
	void deactivate();
};
#endif