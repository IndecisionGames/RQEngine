#include "RQEngine.h"

using namespace RQEngine;

InputManager* InputManager::instance = 0;
std::unordered_map<unsigned int, bool> InputManager::keyMap;
std::unordered_map<unsigned int, unsigned int> InputManager::keyHeldMap;

InputManager::InputManager() {}

InputManager* InputManager::getInstance() {
    if (instance == 0) {
        instance = new InputManager();
    }
    return instance;
}


void InputManager::pressKey(unsigned int keyID, unsigned int deltaTime) {
    if (keyMap[keyID] == true) {
        keyHeldMap[keyID] += deltaTime;
    } else {
        keyMap[keyID] = true;
        keyHeldMap[keyID] = 0;
    }
}

void InputManager::releaseKey(unsigned int keyID) {
    keyMap[keyID] = false;
    keyHeldMap[keyID] = 0;
}


bool InputManager::isKeyPressed(unsigned int keyID) {
    return keyMap[keyID];
}

unsigned int InputManager::isKeyHeld(unsigned int keyID) {
    return keyHeldMap[keyID];
}