#pragma once

#include <glm/glm.hpp>

namespace RQEngine
{

    class Camera3D {

        public:
            Camera3D();

            void init(int screenWidth, int screenHeight, float fov = 45.0f, float near = 0.1f, float far = 100.0f, glm::vec3 defaultPositionVal = glm::vec3(0,0,0), glm::vec2 defaultRotationVal = glm::vec2(0,0));

            void setPosition(glm::vec3 pos);
            void setRotation(glm::vec2 rot);
            void reset();

            void translate(glm::vec3 translate);
            void translateRelative(glm::vec3 translate);
            void rotate(glm::vec2 rotationVal);

            glm::mat4 getProjection();
            glm::mat4 getView();
            glm::vec3 getPosition();
            glm::vec2 getDirection();
            glm::vec2 getRotation();

        private:

            glm::mat4 projection;

            glm::vec3 position;
            glm::vec3 direction;
            glm::vec2 rotation;

            glm::vec3 defaultPosition;
            glm::vec2 defaultRotation;

            void updateDirection();
    };

} // namespace RQEngine
