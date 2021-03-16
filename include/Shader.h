#pragma once

#include <gl/glew.h>
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
