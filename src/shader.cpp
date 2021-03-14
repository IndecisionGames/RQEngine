#include "Shader.h"

#include <gl/glew.h>
#include <gl/glu.h>


void printProgramLog(GLuint program) {
    //Make sure name is program
    if (glIsProgram(program)) {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) printf("%s\n", infoLog);

        //Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a program\n", program);
    }
}

void printShaderLog(GLuint shader) {
    //Make sure name is shader
    if (glIsShader(shader)) {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) printf("%s\n", infoLog);

        //Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a shader\n", shader);
    }
}


using namespace RQEngine;

Shader::Shader(std::string vertexCode, std::string fragmentCode){
    GLint success;

    ID = glCreateProgram();

    // Complie Vertex Shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vShaderCode = vertexCode.c_str();
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Unable to compile vertex shader %d!\n", vertex);
        printShaderLog(vertex);
    }

      // Complie Fragment Shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* fShaderCode = fragmentCode.c_str();
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Unable to compile fragment shader %d!\n", fragment);
        printShaderLog(fragment);
    }

    // Link Shaders
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        printf("Error linking program %d!\n", ID);
        printProgramLog(ID);
    }

    // Shaders are linked so can be deleted
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}

GLuint Shader::getID(){
    return ID;
}

void Shader::free(){
    glDeleteProgram(ID);
}
