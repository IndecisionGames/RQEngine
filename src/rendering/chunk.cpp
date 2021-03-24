#include "Chunk.h"

using namespace RQEngine;

Chunk::Chunk() { // Create the blocks
    m_blocks = new Block **[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_SIZE];
        for(int j = 0; j < CHUNK_SIZE; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk() { // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            delete[] m_blocks[i][j];
        }
        delete[]m_blocks[i];
    }
    delete[] m_blocks;
}
