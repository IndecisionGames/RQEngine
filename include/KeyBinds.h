#pragma once

#include <unordered_map>


namespace RQEngine
{

    typedef std::pair<unsigned int, unsigned int> keyBind;

    class KeyBinds {

        public:

            static KeyBinds* getInstance();

            //TODO: Use variadic function
            static void loadKeyBinds(keyBind keyBindings[], int NumBindings);
            static void updateKeyBind(keyBind keyBinding);

            static unsigned int getKey(unsigned int customKeyID);

        private:

            KeyBinds();

            static KeyBinds* instance;

            static std::unordered_map<unsigned int, unsigned int> keyBindingMap;

    };

} // namespace RQEngine
