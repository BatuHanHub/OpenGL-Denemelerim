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
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main() {
    glfwInit(); // <- glfw'yi başlat

    /* OpenGL ver 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE); // OpenGL profili

    GLFWwindow* win = glfwCreateWindow(800,800, "OpenGL dersi", NULL, NULL);

    if(!win) {
        std::cerr << "Pencere olusturulmadi!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(win); // OpenGL için varsayılan pencere ayarla

    gladLoadGL(); // OpenGL'yi yükle
    glViewport(0,0,800,800); // OpenGL sınırı

    // Üçgenin vertex koordinatları
    GLfloat vertexs[] = {
        0.0f,  0.5f, 0.0f,  
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f 
   };
   

   /* OpenGL'nin ilginç pipeline'ı :) */

    // Vertex Shader //
    GLuint vtx = glCreateShader(GL_VERTEX_SHADER); // Shader oluşturuldu
    glShaderSource(vtx, 1, &vsc, NULL); // Shaderı belleğe çekti
    glCompileShader(vtx); // Shader makine koduna çevrildi

    // Fragment Shader(bir öncekinin aynı işleri) //
    GLuint fgx = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fgx, 1, &fsc, NULL); 
    glCompileShader(fgx);

    // Shaderlar için program oluşturuldu //
    GLuint prg = glCreateProgram();
    glAttachShader(prg, vtx); // Vertex Shader'ı programa ekle
    glAttachShader(prg, fgx); // Fragment Shader'ı programa ekle
    glLinkProgram(prg); // Hepsini birleştir

    glDeleteShader(vtx); // shader'ı sil
    glDeleteShader(fgx); // shader'ı sil


    GLuint VBO, VAO; // vertex buffer object, vertex array object

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

   /* -- */
   

    while(!glfwWindowShouldClose(win)) {

        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prg);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}