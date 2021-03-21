#include "KeyBinds.h"

using namespace RQEngine;

KeyBinds* KeyBinds::instance = 0;
std::unordered_map<unsigned int, unsigned int> KeyBinds::keyBindingMap;

KeyBinds::KeyBinds() {}

KeyBinds* KeyBinds::getInstance() {
    if (instance == 0) {
        instance = new KeyBinds();
    }
    return instance;
}

void KeyBinds::load(unsigned int name, unsigned int key){
    keyBindingMap[name] = key;
}

void KeyBinds::update(unsigned int name, unsigned int key) {
    KeyBinds::load(name, key);
}

unsigned int KeyBinds::getKey(unsigned int customKeyID) {
    return keyBindingMap[customKeyID];
}
