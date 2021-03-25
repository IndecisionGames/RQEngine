#include "InputManager.h"
#include <iostream>

using namespace RQEngine;


InputManager* InputManager::instance = 0;
std::unordered_map<unsigned int, bool> InputManager::keyMap;
std::unordered_map<unsigned int, int> InputManager::keyHeldMap;
glm::uvec2 InputManager::mousePosition;
glm::ivec2 InputManager::mouseMotion;
glm::ivec2 InputManager::mouseWheelMotion;

InputManager::InputManager() {}

InputManager* InputManager::getInstance() {
    if (instance == 0) {
        instance = new InputManager();
    }
    return instance;
}

glm::uvec2 InputManager::getMousePosition(){
    return mousePosition;
}

glm::ivec2 InputManager::getMouseMotion(){
    return mouseMotion;
}

glm::ivec2 InputManager::getMouseWheelMotion(){
    return mouseWheelMotion;
}

void InputManager::handleEvent(SDL_Event& e){
 switch (e.type) {
    case SDL_KEYDOWN:
        keyMap[e.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        keyMap[e.key.keysym.sym] = false;
        keyHeldMap[e.key.keysym.sym] = -1;
        break;

    case SDL_MOUSEBUTTONDOWN:
        keyMap[e.button.button] = true;
        break;
    case SDL_MOUSEBUTTONUP :
        keyMap[e.button.button] = false;
        keyHeldMap[e.button.button] = -1;
        break;

    case SDL_MOUSEMOTION:
        mousePosition = glm::uvec2(e.motion.x, e.motion.y);
        mouseMotion = glm::ivec2(e.motion.xrel, e.motion.yrel);
        break;
    case SDL_MOUSEWHEEL:
        mouseWheelMotion = glm::ivec2(e.wheel.x, e.wheel.y);
        break;
    }
}

void InputManager::update(unsigned int deltaTime) {
     for(auto it = keyMap.begin(); it != keyMap.end(); it++){
         if(it->second){
             keyHeldMap[it->first] += deltaTime;
         } else {
             keyHeldMap[it->first] = 0;
         }
    }
    mouseMotion = glm::ivec2(0, 0);
    mouseWheelMotion = glm::ivec2(0, 0);
}

bool InputManager::isKeyPressed(unsigned int keyID) {
    return keyMap[keyID];
}

bool InputManager::isKeyPressedInitial(unsigned int keyID) {
    return keyMap[keyID] && !keyHeldMap[keyID];
}

bool InputManager::isKeyReleasedInitial(unsigned int keyID) {
    return keyHeldMap[keyID] == -1;
}

unsigned int InputManager::isKeyHeld(unsigned int keyID) {
    return keyHeldMap[keyID];
}
