#pragma once

#include <gl/glew.h>
#include <string>

namespace RQEngine
{

    class Shader {

        public:
            // TODO: From FilePath
            // Shader(const char* vertexPath, const char* fragmentPath);
            Shader(std::string vertexCode, std::string fragmentCode);

            GLuint getID();
            void use();

            void free();

        private:
            // program ID
            GLuint ID;
    };

} // namespace RQEngine
