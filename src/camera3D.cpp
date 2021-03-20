#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera3D.h"

using namespace RQEngine;


Camera3D::Camera3D() {}


void Camera3D::init(int screenWidth, int screenHeight, float fov, float near, float far, glm::vec3 defaultPositionVal, glm::vec2 defaultRotationVal){
    projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, near, far);
    // Or, for an ortho camera :
    // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    defaultPosition = defaultPositionVal;
    defaultRotation = defaultRotationVal;

    position = defaultPositionVal;
    rotation = defaultRotationVal;
    updateDirection();
}

void Camera3D::setPosition(glm::vec3 postionVal){
    position = postionVal;
}

void Camera3D::setRotation(glm::vec2 rotationVal){
    rotation = rotationVal;
    updateDirection();
}

void Camera3D::reset(){
    position = defaultPosition;
    rotation = defaultRotation;
    updateDirection();
}

void Camera3D::updateDirection(){
    // prevent screen flip
    if (rotation.y > 89.9f){
        rotation.y = 89.9f;
    }
    if (rotation.y < -89.9f){
        rotation.y = -89.9f;
    }


    direction = glm::normalize(
            glm::vec3(
                glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x)),
                glm::sin(glm::radians(rotation.y)),
                glm::cos(glm::radians(rotation.y)) * glm::sin(glm::radians(rotation.x))
	        )
        );
}


void Camera3D::translate(glm::vec3 translate){
    position += translate;

}
void Camera3D::translateRelative(glm::vec3 translate){
    // Need to find the x, y, z components relative to new direction.
    // Z if moving forward in the direction you are facing, it is the Z component
    glm::vec3 xComponent = glm::cross(direction, glm::vec3(0,-1,0));    // Cross Product with Y axis gives a vector perpendicular along the new X axis
    glm::vec3 yComponent = glm::cross(direction, -xComponent);          // Cross Product with new X axis gives a vector perpendicular along the new Y axis

    position += direction * translate.z + xComponent * translate.x + yComponent * translate.y;
}

void Camera3D::rotate(glm::vec2 rotationVal){
    rotation += rotationVal;
    updateDirection();
}

glm::mat4 Camera3D::getProjection(){
    return projection;
}

glm::mat4 Camera3D::getView(){
    return glm::lookAt(
            position,               // Camera in World Space
            position + direction,   // Point to look at
            glm::vec3(0,1,0)        // Head is up (set to 0,-1,0 to look upside-down)
        );
}

glm::vec3 Camera3D::getPosition(){
    return position;
}

glm::vec2 Camera3D::getDirection(){
    return direction;
}

glm::vec2 Camera3D::getRotation(){
    return rotation;
}
