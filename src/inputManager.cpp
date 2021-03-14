#include "InputManager.h"


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


void InputManager::pressKey(unsigned int keyID) {
    keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
    keyMap[keyID] = false;
    keyHeldMap[keyID] = 0;
}


void InputManager::update(unsigned int deltaTime) {
     for(auto it = keyMap.begin(); it != keyMap.end(); it++){
         if(it->second){
             keyHeldMap[it->first] += deltaTime;
         }
    }
}


bool InputManager::isKeyPressed(unsigned int keyID) {
    return keyMap[keyID];
}

unsigned int InputManager::isKeyHeld(unsigned int keyID) {
    return keyHeldMap[keyID];
}