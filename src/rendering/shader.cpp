#include "Shader.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace RQEngine;

Shader::Shader(){};

GLuint Shader::CreateShader(const std::string &shaderPath, GLenum shaderType) {
    if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER && shaderType != GL_GEOMETRY_SHADER) {
        printf("Invalid/Unsupported Shader type %u.\n", shaderType);
    }
    // Create the shader
    GLuint shader = glCreateShader(shaderType);

    // Read shader code from file
    std::string shaderCode;
    std::ifstream shaderStream(shaderPath, std::ios::in);
    if (shaderStream.is_open()){
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    } else {
        printf("Could not load shader from %s.\n", shaderPath.c_str());
    }
    const char *sourcePointer = shaderCode.c_str();
    glShaderSource(shader, 1, &sourcePointer, NULL);

    // Compile shader
    printf("Compiling shader : %s\n", shaderPath.c_str());
    glCompileShader(shader);

    // Check shader
    GLint status = GL_FALSE;
    int infoLogLength;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0){
        std::vector<char> shaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }

    return shader;
}

void Shader::initProgram(const std::vector<GLuint> &shaderList) {
    printf("Initialising shader program\n");
    program = glCreateProgram();

    for (size_t i = 0; i < shaderList.size(); i++) {
        glAttachShader(program, shaderList[i]);
    }

    glLinkProgram(program);

    // Check program
    GLint status = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0){
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    for (size_t i = 0; i < shaderList.size(); i++) {
        glDetachShader(program, shaderList[i]);
        glDeleteShader(shaderList[i]);
    }
}

void Shader::use(){
    glUseProgram(program);
}

GLuint* Shader::getID(){
    return &program;
}

void Shader::free(){
    glDeleteProgram(program);
}
