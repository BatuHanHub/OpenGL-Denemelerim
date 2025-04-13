#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Vertex Shader
const char* vsc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader
const char* fsc = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* win = glfwCreateWindow(800,800,"Dota 3", NULL, NULL);

    if(!win) {
        std::cerr << "Pencere calistirilmiyor!?" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(win);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Yoooo!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800);

    GLuint vtx = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtx, 1, &vsc, NULL);
    glCompileShader(vtx);

    GLuint fgx = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fgx, 1, &fsc, NULL);
    glCompileShader(fgx);


    GLuint p = glCreateProgram();
    glAttachShader(p, vtx);
    glAttachShader(p, fgx);
    glLinkProgram(p);

    glDeleteShader(vtx);
    glDeleteShader(fgx);


    GLfloat vertex[] = {
        -0.5f,  0.5f, 0.0f, // ust
        0.5f, -0.5f, 0.0f,  // sag
        -0.5f, -0.5f, 0.0f  // sol
   };
   

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    while(!glfwWindowShouldClose(win)) {
        glClearColor(1.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(p);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}