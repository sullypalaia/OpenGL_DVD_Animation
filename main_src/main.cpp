#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <random>

#include "../src/shaderClass.hpp"
#include "../src/VAO.hpp"
#include "../src/VBO.hpp"
#include "../src/EBO.hpp"

//vertex shader source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//fragment shader source
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);\n"
"}\n\0";

//indices
GLuint indices[] = {
	3, 2, 0,
	0, 3, 1
};

int main() {
    glfwInit();
    //glfw settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //creates and initialized an 800px*800px window
    GLFWwindow *window = glfwCreateWindow(800, 800, "OpenGL Loading Animation", NULL, NULL);
    if (window == NULL) {
        std::cout << "glfw window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //loads glad and creates the viewport

    gladLoadGL();
	glViewport(0, 0, 800, 800);

    //creates the shader program
    Shader shaderProgram(vertexShaderSource, fragmentShaderSource);

    float x = 0.0f;
    float y = 0.0f;
    std::random_device rd0;
    std::mt19937 gen0(rd0());
    std::uniform_real_distribution<> dis0(0.0, 0.05);
    float incX = (float(dis0(gen0)));
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<> dis1(0.0, 0.05);
    float incY = (float)(dis1(gen1));
    float startX = 0.0f;
    //proccesses events while the window is open
    while (!glfwWindowShouldClose(window)) {
        if ((x >= 1.0f - (startX + 0.2f))/*right*/ || (x <= -1.0f - startX)/*left*/) {
            incX *= -1.0f;
            x += incX;
            y += incY;
        }
        else if ((y <= -1.0f)/*bottom*/ || (y >= 0.8f)/*top*/) {
            incY *= -1.0f;
            x += incX;
            y += incY;
        }
        else {
            x += incX;
            y += incY;
        }

        //vertices
        GLfloat vertices[] = {
            (startX + x), (0.2f + y), (0.0f), //top left
            ((startX + 0.2f) + x), (0.2f + y), (0.0f), //top right
            (startX + x), (y), (0.0f), //bottom left
            ((startX + 0.2f) + x), (y), (0.0f) //bottom right
        }; 

        //creates the VAO, binds it, creates the VBO and EBO, links them, and unbinds all of them
        VAO VAO1;
        VAO1.bind();
        VBO VBO1(vertices, sizeof(vertices));
        EBO EBO1(indices, sizeof(indices));
        VAO1.linkVBO(VBO1, 0);
        VAO1.unbind();
        VBO1.unbind();
        EBO1.unbind();

        //assigns the color for the window, swaps the buffers, and polls events
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activates the shader program, binds the VAO, and draws the elements
        shaderProgram.activate();
		VAO1.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //swaps the buffers
        glfwSwapBuffers(window);

        //deletes the VAO, VBO, and EBO
        VAO1.deactivate();
        VBO1.deactivate();
        EBO1.deactivate();

        //polls the window events
        glfwPollEvents();
    }

    //deletes everything and terminates glfw
    shaderProgram.deactivate();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}