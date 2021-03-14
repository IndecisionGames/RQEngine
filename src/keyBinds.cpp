#include "KeyBinds.h"
#include <stdarg.h>

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

void KeyBinds::loadKeyBinds(keyBind keyBindings[], int NumBindings){
     for(int i = 0; i < NumBindings; i++){
        keyBindingMap[keyBindings[i].first] = keyBindings[i].second;
    }
}

void KeyBinds::updateKeyBind(keyBind keyBinding) {
    keyBindingMap[keyBinding.first] = keyBinding.second;
}

unsigned int KeyBinds::getKey(unsigned int customKeyID) {
    return keyBindingMap[customKeyID];
}
