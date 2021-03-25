#pragma once

#include "RQEngine.h"
    
// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
 // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
GLfloat vertexData[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
        
     1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,

     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,

     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};

// One color for each vertex.
GLfloat colourData[] = {
    RED.x, RED.y, RED.z,
    GREEN.x, GREEN.y, GREEN.z,
    BLUE.x, BLUE.y, BLUE.z,

    GREEN.x, GREEN.y, GREEN.z,
    GREEN.x, GREEN.y, GREEN.z,
    GREEN.x, GREEN.y, GREEN.z,

    BLUE.x, BLUE.y, BLUE.z,
    BLUE.x, BLUE.y, BLUE.z,
    BLUE.x, BLUE.y, BLUE.z,

    GREEN.x, GREEN.y, GREEN.z,
    GREEN.x, GREEN.y, GREEN.z,
    GREEN.x, GREEN.y, GREEN.z,

    RED.x, RED.y, RED.z,
    BLUE.x, BLUE.y, BLUE.z,
    GREEN.x, GREEN.y, GREEN.z,

    BLUE.x, BLUE.y, BLUE.z,
    BLUE.x, BLUE.y, BLUE.z,
    BLUE.x, BLUE.y, BLUE.z,

    MAGENTA.x, MAGENTA.y, MAGENTA.z,
    MAGENTA.x, MAGENTA.y, MAGENTA.z,
    MAGENTA.x, MAGENTA.y, MAGENTA.z,

    CYAN.x, CYAN.y, CYAN.z,
    CYAN.x, CYAN.y, CYAN.z,
    CYAN.x, CYAN.y, CYAN.z,

    CYAN.x, CYAN.y, CYAN.z,
    CYAN.x, CYAN.y, CYAN.z,
    CYAN.x, CYAN.y, CYAN.z,

    YELLOW.x, YELLOW.y, YELLOW.z,
    YELLOW.x, YELLOW.y, YELLOW.z,
    YELLOW.x, YELLOW.y, YELLOW.z,

    YELLOW.x, YELLOW.y, YELLOW.z,
    YELLOW.x, YELLOW.y, YELLOW.z,
    YELLOW.x, YELLOW.y, YELLOW.z,

    MAGENTA.x, MAGENTA.y, MAGENTA.z,
    MAGENTA.x, MAGENTA.y, MAGENTA.z,
    MAGENTA.x, MAGENTA.y, MAGENTA.z,
};
