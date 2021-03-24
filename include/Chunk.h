#pragma once

#include <Block.h>
#include <Shader.h>

namespace RQEngine {

    class Chunk {
        public:
            Chunk();
            ~Chunk();
            void Update(float dt);
            void Render(); //TODO: this should take in a OpenGL renderer
            static const int CHUNK_SIZE = 16;
        
        private:
            Block * * * m_blocks;
    };

} // namespace RQEngine