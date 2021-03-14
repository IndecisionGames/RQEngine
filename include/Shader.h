#pragma once

#include <string>
#include <gl/glew.h>

namespace RQEngine
{

    class Shader {

        public:
            // program ID
            GLuint ID;
        
            // TODO: From FilePath
            // Shader(const char* vertexPath, const char* fragmentPath);
            Shader(std::string vertexCode, std::string fragmentCode);

            void use();
    };

} // namespace RQEngine