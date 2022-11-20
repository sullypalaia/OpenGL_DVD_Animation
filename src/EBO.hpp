#ifndef EBO_CLASS_HPP
#define EBO_CLASS_HPP

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	void bind();
	void unbind();
	void deactivate();
};

#endif