#pragma once

#include <GL/glew.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl/gl.h>
#include <gl/glu.h>
#endif
#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>

namespace RQEngine
{

    class Shader {

        public:
            Shader();

            static GLuint CreateShader(const std::string &shaderPath, GLenum shaderType);
            void initProgram(const std::vector<GLuint> &shaderList);
            GLuint* getID();
            void use();
            void free();

        private:
            GLuint program;
    };

} // namespace RQEngine
