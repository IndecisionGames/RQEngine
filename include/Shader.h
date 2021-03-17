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

namespace RQEngine
{

    class Shader {

        public:
            Shader(const char* vertexPath, const char* fragmentPath);

            GLuint getID();
            void use();

            void free();

        private:
            GLuint ProgramID;
    };

} // namespace RQEngine
